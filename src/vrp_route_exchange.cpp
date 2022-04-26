#include "vrp/vrp_route_exchange.h"

namespace daa {

VrpRouteExchange::VrpRouteExchange(Type type) : type_{type} {}

VrpSolution VrpRouteExchange::Execute(const VrpProblem& problem,
                                      const VrpSolution& solution) {
  VehiclesPaths vehicle_paths{solution.GetVehiclesPaths()};
  DistanceMatrix distance_matrix = problem.GetDistanceMatrix();
  ExchangeInfo exchange_info{GetExchangeInfo(solution)};
  ClientInfo old_first_client{exchange_info.GetFirstClient()};
  ClientInfo old_second_client{exchange_info.GetSecondClient()};
  std::size_t first_client_distance{
      distance_matrix[old_first_client.GetComeFrom()]
                     [old_second_client.GetId()]};
  ClientInfo first_client{old_second_client.GetId(), first_client_distance,
                          old_first_client.GetComeFrom()};
  std::size_t second_client_distance{
      distance_matrix[old_second_client.GetComeFrom()]
                     [old_first_client.GetId()]};
  ClientInfo second_client{old_first_client.GetId(), second_client_distance,
                           old_second_client.GetComeFrom()};
  vehicle_paths[exchange_info.GetFirstRoute()]
               [exchange_info.GetFirstPosition()] = first_client;
  vehicle_paths[exchange_info.GetSecondRoute()]
               [exchange_info.GetSecondPosition()] = second_client;

  if (exchange_info.GetFirstPosition() <
      vehicle_paths[exchange_info.GetFirstRoute()].size() - 1) {
    std::size_t first_client_next_id{
        vehicle_paths[exchange_info.GetFirstRoute()]
                     [exchange_info.GetFirstPosition() + 1]
                         .GetId()};
    std::size_t first_client_next_distance{
        distance_matrix[first_client.GetId()][first_client_next_id]};
    ClientInfo first_client_next{
        first_client_next_id, first_client_next_distance, first_client.GetId()};
    vehicle_paths[exchange_info.GetFirstRoute()]
                 [exchange_info.GetFirstPosition() + 1] = first_client_next;
  }
  if (exchange_info.GetSecondPosition() <
      vehicle_paths[exchange_info.GetSecondRoute()].size() - 1) {
    std::size_t second_client_next_id{
        vehicle_paths[exchange_info.GetSecondRoute()]
                     [exchange_info.GetSecondPosition() + 1]
                         .GetId()};
    std::size_t second_client_next_distance{
        distance_matrix[second_client.GetId()][second_client_next_id]};
    ClientInfo second_client_next{second_client_next_id,
                                  second_client_next_distance,
                                  second_client.GetId()};
    vehicle_paths[exchange_info.GetSecondRoute()]
                 [exchange_info.GetSecondPosition() + 1] = second_client_next;
  }
}

ExchangeInfo VrpRouteExchange::GetExchangeInfo(const VrpSolution& solution) {
  std::size_t first_route{std::rand() % solution.GetVehiclesPaths().size()};
  std::size_t second_route{};
  if (type_ == Type::kIntra)
    second_route = first_route;
  else
    second_route = std::rand() % solution.GetVehiclesPaths().size();
  std::size_t first_node{std::rand() %
                         solution.GetVehiclesPaths()[first_route].size()};
  std::size_t second_node{std::rand() %
                          solution.GetVehiclesPaths()[second_route].size()};

  while (first_node == second_node)
    second_node =
        std::rand() % solution.GetVehiclesPaths()[second_route].size();
  ClientInfo first_client{solution.GetVehiclesPaths()[first_route][first_node]};
  ClientInfo second_client{
      solution.GetVehiclesPaths()[second_route][second_node]};

  return ExchangeInfo{first_client, second_client, first_node,
                      second_node,  first_route,   second_route};
}

}  // namespace daa
