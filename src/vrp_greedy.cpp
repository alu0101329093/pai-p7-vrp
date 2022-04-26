#include "vrp/vrp_greedy.h"

#include <iostream>

namespace daa {

/**
 * @brief Construct a new Vrp Greedy:: Vrp Greedy object
 *
 */
VrpGreedy::VrpGreedy() {}

/**
 * @brief Solve greedy problem
 *
 * @param problem
 * @return VrpSolution
 */
VrpSolution VrpGreedy::Solve(const VrpProblem& problem,
                             const std::unique_ptr<VrpOptions>&) {
  VehiclesPaths vehicles_paths{problem.GetVehiclesAmount(),
                               std::vector<ClientInfo>{}};
  std::set<std::size_t> clients_set{GenerateClientsSet(problem)};
  auto clients_to_base_queue = GenerateCliensToBaseQueue(problem);
  for (std::size_t i = 0; i < vehicles_paths.size(); ++i) {
    vehicles_paths[i].push_back(clients_to_base_queue.top());
    clients_set.erase(clients_to_base_queue.top().GetId());
    clients_to_base_queue.pop();
  }

  while (!clients_set.empty()) {
    ClientInfo best_option{GetBestOption(problem, clients_set, vehicles_paths)};
    for (auto& path : vehicles_paths) {
      std::size_t current_client{path.back().GetId()};
      if (current_client == best_option.GetComeFrom()) {
        path.push_back(best_option);
        clients_set.erase(best_option.GetId());
      }
    }
  }

  return {SetReturnPaths(problem, vehicles_paths)};
}

/**
 * @brief Generete client list to start the problem
 *
 * @param problem
 * @return std::priority_queue<ClientInfo, std::vector<ClientInfo>,
 * std::greater<ClientInfo>>
 */
std::priority_queue<ClientInfo, std::vector<ClientInfo>,
                    std::greater<ClientInfo>>
VrpGreedy::GenerateCliensToBaseQueue(const VrpProblem& problem) {
  std::priority_queue<ClientInfo, std::vector<ClientInfo>,
                      std::greater<ClientInfo>>
      clients_queue{};
  for (std::size_t i = 1; i <= problem.GetClientsAmount(); ++i) {
    clients_queue.push({i, problem.GetDistanceMatrix()[0][i], 0});
  }
  return clients_queue;
}

/**
 * @brief Get paths adding return to base
 *
 * @param problem
 * @param vehicles_paths
 * @return VehiclesPaths
 */
VehiclesPaths VrpGreedy::SetReturnPaths(const VrpProblem& problem,
                                        const VehiclesPaths& vehicles_paths) {
  VehiclesPaths return_path{vehicles_paths};
  for (std::size_t i = 0; i < return_path.size(); ++i) {
    ClientInfo node{return_path[i].back()};
    return_path[i].push_back(
        {0, problem.GetDistanceMatrix()[node.GetId()][0], 0});
  }
  return return_path;
}

/**
 * @brief Generate clients set to start the problem
 *
 * @param problem
 * @return std::set<std::size_t>
 */
std::set<std::size_t> VrpGreedy::GenerateClientsSet(const VrpProblem& problem) {
  std::set<std::size_t> clients_set{};
  for (std::size_t i = 1; i <= problem.GetClientsAmount(); ++i) {
    clients_set.insert(i);
  }
  return clients_set;
}

/**
 * @brief Get best client with current paths
 *
 * @param problem
 * @param clients_set
 * @param vehicles_paths
 * @return ClientInfo
 */
ClientInfo VrpGreedy::GetBestOption(const VrpProblem& problem,
                                    std::set<std::size_t> clients_set,
                                    const VehiclesPaths& vehicles_paths) {
  ClientsQueue clients_queue{};
  for (auto path : vehicles_paths) {
    std::size_t current_client{path.back().GetId()};
    for (auto client : clients_set) {
      clients_queue.push({client,
                          problem.GetDistanceMatrix()[current_client][client],
                          current_client});
    }
  }
  return clients_queue.top();
}

}  // namespace daa
