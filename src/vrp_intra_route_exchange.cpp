#include "vrp/vrp_intra_route_exchange.h"

namespace daa {

VrpSolution VrpIntraRouteExchange::Execute(const VrpProblem& problem,
                                           const VrpSolution& solution) {
  std::size_t route{std::rand() % solution.GetVehiclesPaths().size()};
  while (solution.GetVehiclesPaths()[route].size())
    route = std::rand() % solution.GetVehiclesPaths().size();
  std::size_t first_node{std::rand() %
                         solution.GetVehiclesPaths()[route].size()};
  std::size_t second_node{std::rand() %
                          solution.GetVehiclesPaths()[route].size()};
  while (first_node == second_node)
    second_node = std::rand() % solution.GetVehiclesPaths()[route].size();
  ClientInfo first_client{solution.GetVehiclesPaths()[route][first_node]};
}

VrpIntraRouteExchange::GetClientsToExchange() {}

}  // namespace daa
