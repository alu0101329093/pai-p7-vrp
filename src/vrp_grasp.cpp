#include "vrp/vrp_grasp.h"

namespace daa {

/**
 * @brief Solve grasp problem
 *
 * @param problem
 * @param iterations
 * @param random_solutions_amount
 * @param max_unchanged_iterations
 * @return VrpGraspSolution - Solutions history and best solution
 */
VrpGraspSolution VrpGrasp::Solve(const VrpProblem& problem,
                                 std::size_t iterations,
                                 std::size_t random_solutions_amount,
                                 std::size_t max_unchanged_iterations) {
  std::srand(std::time(nullptr));
  std::vector<VrpSolution> solutions_history{};
  std::size_t best_solution_distance{SIZE_MAX};
  std::size_t best_solution{};
  std::size_t unchanged_iterations{};

  for (std::size_t i = 0;
       i < iterations && unchanged_iterations < max_unchanged_iterations; ++i) {
    ClientsSet clients_set{GenerateClientSet(problem)};
    VrpSolution partial_solution{
        SetInitialPath(problem, random_solutions_amount, clients_set)};
    VrpSolution solution{SolveStartedProblem(
        problem, partial_solution, random_solutions_amount, clients_set)};
    solutions_history.push_back(solution);
    std::size_t distance_sum{solution.GetPathsDistanceSum()};

    if (distance_sum < best_solution_distance) {
      best_solution = solutions_history.size() - 1;
      best_solution_distance = distance_sum;
      unchanged_iterations = 0;
    } else {
      ++unchanged_iterations;
    }
  }

  return VrpGraspSolution{solutions_history, best_solution};
}

/**
 * @brief Generete clients set for one problem
 *
 * @param problem
 * @return ClientsSet
 */
ClientsSet VrpGrasp::GenerateClientSet(const VrpProblem& problem) {
  ClientsSet clients_set{};
  for (std::size_t i = 1; i <= problem.GetClientsAmount(); ++i) {
    clients_set.insert(i);
  }
  return clients_set;
}

/**
 * @brief Get best options for a list of clients
 *
 * @param problem
 * @param clients_set
 * @param current_clients
 * @param amount
 * @return std::set<ClientInfo>
 */
std::set<ClientInfo> VrpGrasp::GetClientsBestOptions(
    const VrpProblem& problem, const ClientsSet& clients_set,
    const ClientsSet& current_clients, std::size_t amount) {
  ClientsQueue clients_queue{};
  for (auto current_client : current_clients) {
    for (auto client : clients_set) {
      clients_queue.push(ClientInfo{
          client, problem.GetDistanceMatrix()[current_client][client],
          current_client});
    }
  }
  std::set<ClientInfo> best_options{};
  for (std::size_t i = 0; i < amount && !clients_queue.empty(); ++i) {
    best_options.insert(clients_queue.top());
    clients_queue.pop();
  }
  return best_options;
}

/**
 * @brief Select random option in a list
 *
 * @param options
 * @return ClientInfo
 */
ClientInfo VrpGrasp::GetRandomOption(const std::set<ClientInfo>& options) {
  auto iterator{options.cbegin()};
  if (options.size() == 1) return *iterator;
  std::size_t selected_option{std::rand() % options.size()};
  std::advance(iterator, selected_option);
  return *iterator;
}

/**
 * @brief Set starting paths for a started greedy problem
 *
 * @param problem
 * @param random_solutions_amount
 * @param clients_set
 * @return VrpSolution
 */
VrpSolution VrpGrasp::SetInitialPath(const VrpProblem& problem,
                                     std::size_t random_solutions_amount,
                                     ClientsSet& clients_set) {
  std::set<ClientInfo> initial_options{GetClientsBestOptions(
      problem, clients_set, {0},
      random_solutions_amount * problem.GetVehiclesAmount())};

  VehiclesPaths vehicles_paths{problem.GetVehiclesAmount(),
                               std::vector<ClientInfo>{}};
  for (std::size_t i = 0;
       i < problem.GetVehiclesAmount() && !initial_options.empty(); ++i) {
    ClientInfo option{GetRandomOption(initial_options)};
    vehicles_paths[i].push_back(option);
    initial_options.erase(option);
    clients_set.erase(option.GetId());
  }

  return {vehicles_paths};
}

/**
 * @brief Solve problem with a part already done
 *
 * @param problem
 * @param partial_solution
 * @param random_solutions_amount
 * @param clients_set
 * @return VrpSolution
 */
VrpSolution VrpGrasp::SolveStartedProblem(const VrpProblem& problem,
                                          const VrpSolution& partial_solution,
                                          std::size_t random_solutions_amount,
                                          ClientsSet& clients_set) {
  VehiclesPaths vehicles_paths{partial_solution.GetVehiclesPaths()};
  while (!clients_set.empty()) {
    ClientsSet current_clients{};
    for (const auto& path : vehicles_paths) {
      if (path.size() > 0)
        current_clients.insert(path.back().GetId());
      else
        current_clients.insert(0);
    }

    std::set<ClientInfo> best_options{GetClientsBestOptions(
        problem, clients_set, current_clients, random_solutions_amount)};
    ClientInfo option{GetRandomOption(best_options)};
    for (auto& path : vehicles_paths) {
      if (option.GetComeFrom() == 0) {
        if (path.size() == 0) {
          path.push_back(option);
          clients_set.erase(option.GetId());
          break;
        }
      } else {
        if (path.back().GetId() == option.GetComeFrom()) {
          path.push_back(option);
          clients_set.erase(option.GetId());
          break;
        }
      }
    }
  }

  return {SetReturnPaths(problem, vehicles_paths)};
}

/**
 * @brief Get paths adding return to base
 *
 * @param problem
 * @param vehicles_paths
 * @return VehiclesPaths
 */
VehiclesPaths VrpGrasp::SetReturnPaths(const VrpProblem& problem,
                                       const VehiclesPaths& vehicles_paths) {
  VehiclesPaths return_path{vehicles_paths};
  for (std::size_t i = 0; i < return_path.size(); ++i) {
    ClientInfo node{return_path[i].back()};
    return_path[i].push_back(
        {0, problem.GetDistanceMatrix()[node.GetId()][0], 0});
  }
  return return_path;
}

}  // namespace daa
