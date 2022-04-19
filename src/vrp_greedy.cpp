#include "vrp/vrp_greedy.h"

#include <iostream>

namespace daa {

VrpGreedy::VrpGreedy() {}

VrpSolution VrpGreedy::Solve(const VrpProblem& problem) {
  VehiclesPaths vehicles_paths{problem.GetVehiclesAmount(),
                               std::vector<ClientInfo>{}};

  auto clients_list = GenerateClientList(problem);
  for (std::size_t i = 0; i < vehicles_paths.size(); ++i) {
    vehicles_paths[i].push_back(clients_list.top());
    clients_list.pop();
  }
  while (!clients_list.empty()) {
    std::size_t current_client{clients_list.top().GetId()};
    clients_list.pop();
    std::size_t best_path{};
    std::size_t best_distance{SIZE_MAX};
    for (std::size_t i = 0; i < vehicles_paths.size(); ++i) {
      auto path = vehicles_paths[i];
      ClientInfo node{path.back()};
      std::size_t distance{
          problem.GetDistanceMatrix()[node.GetId()][current_client]};
      if (distance < best_distance) {
        best_distance = distance;
        best_path = i;
      }
    }
    vehicles_paths[best_path].push_back({current_client, best_distance});
  }
  for (std::size_t i = 0; i < vehicles_paths.size(); ++i) {
    ClientInfo node{vehicles_paths[i].back()};
    vehicles_paths[i].push_back(
        {0, problem.GetDistanceMatrix()[node.GetId()][0]});
  }

  return {vehicles_paths};
}

std::priority_queue<ClientInfo, std::vector<ClientInfo>,
                    std::greater<ClientInfo>>
VrpGreedy::GenerateClientList(const VrpProblem& problem) {
  std::priority_queue<ClientInfo, std::vector<ClientInfo>,
                      std::greater<ClientInfo>>
      clients_queue{};
  for (std::size_t i = 1; i <= problem.GetClientsAmount(); ++i) {
    clients_queue.push({i, problem.GetDistanceMatrix()[0][i]});
  }
  return clients_queue;
}

}  // namespace daa
