#include "vrp/vrp_grasp.h"

namespace daa {

VrpGraspSolution VrpGrasp::Solve(const VrpProblem& problem,
                                 std::size_t iterations,
                                 std::size_t random_solutions_amount,
                                 std::size_t max_unchanged_iterations) {
  std::srand(std::time(nullptr));
  std::vector<VrpSolution> solutions_history{};
  std::size_t best_solution{};
  std::size_t unchanged_iterations{};
  for (std::size_t i = 0;
       i < iterations && unchanged_iterations < max_unchanged_iterations; ++i) {
    ClientsSet clients_set{GenerateClientSet(problem)};
    auto initial_path{
        SetInitialPath(problem, random_solutions_amount, clients_set)};
    // std::set<ClientInfo> initial_options{GetClientBestOptions(
    //     problem, clients_list, 0,
    //     random_solutions_amount * problem.GetVehiclesAmount())};
  }
}

ClientsSet VrpGrasp::GenerateClientSet(const VrpProblem& problem) {
  ClientsSet clients_set{};
  for (std::size_t i = 1; i <= problem.GetClientsAmount(); ++i) {
    clients_set.insert(i);
  }
  return clients_set;
}

std::set<ClientInfoFrom> VrpGrasp::GetClientsBestOptions(
    const VrpProblem& problem, const ClientsSet& clients_set,
    const ClientsSet& current_clients, std::size_t amount) {
  ClientsQueue clients_queue{};
  for (auto current_client : current_clients) {
    for (auto client : clients_set) {
      clients_queue.push(
          {current_client,
           ClientInfo{client,
                      problem.GetDistanceMatrix()[current_client][client]}});
    }
  }
  std::set<ClientInfo> best_options{};
  for (std::size_t i = 0; i < amount && !clients_queue.empty(); ++i) {
    best_options.insert(clients_queue.top());
    clients_queue.pop();
  }
  return best_options;
}

ClientInfo VrpGrasp::GetRandomOption(const std::set<ClientInfo>& options) {
  auto iterator{options.cbegin()};
  if (options.size() == 1) return *iterator;
  std::size_t selected_option{std::rand() % options.size()};
  std::advance(iterator, selected_option);
  return *iterator;
}

VrpSolution VrpGrasp::SetInitialPath(const VrpProblem& problem,
                                     std::size_t random_solutions_amount,
                                     ClientsSet& clients_set) {
  std::set<ClientInfo> initial_options{GetClientsBestOptions(
      problem, clients_set, 0,
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

VrpSolution VrpGrasp::SolveStartedGreedy(const VrpProblem& problem,
                                         const VrpSolution& partial_solution,
                                         std::size_t random_solutions_amount,
                                         ClientsSet& clients_set) {
  VehiclesPaths vehicles_paths{partial_solution.GetVehiclesPaths()};
  while (!clients_set.empty()) {
    auto best_options{GetClientsBestOptions(problem, clients_set, )};
  }
}

}  // namespace daa
