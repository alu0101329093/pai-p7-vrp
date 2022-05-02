#include "vrp/vrp_intra_route_exchange.h"

namespace daa {

VrpIntraRouteExchange::VrpIntraRouteExchange() {}

/**
 * @brief Execute the local search by exchange intra route
 *
 * @param problem
 * @param solution
 * @return VrpSolution
 */
VrpSolution VrpIntraRouteExchange::Execute(const VrpProblem& problem,
                                           const VrpSolution& solution) {
  DistanceMatrix distance_matrix = problem.GetDistanceMatrix();
  VrpSolution best_local{solution};
  VrpSolution old_local{solution};

  do {
    old_local = best_local;

    VrpSolution best_solution{best_local};
    VehiclesPaths local_paths{best_local.GetVehiclesPaths()};
    VrpSolution current_solution{best_local};
    for (std::size_t path = 0; path < local_paths.size(); ++path) {
      if (local_paths[path].size() > 3) {
        for (std::size_t i = 1; i < local_paths[path].size() - 1; ++i) {
          for (std::size_t j = i + 1; j < local_paths[path].size() - 1; ++j) {
            VehiclesPaths current_paths{local_paths};
            ExchangePositions(problem, current_paths, path, i, j);
            current_solution.SetVehiclesPaths(current_paths);
            if (current_solution.GetPathsDistanceSum() <
                best_solution.GetPathsDistanceSum()) {
              best_solution.SetVehiclesPaths(current_paths);
            }
          }
        }
      }
    }
  } while (best_local.GetPathsDistanceSum() < old_local.GetPathsDistanceSum());

  return best_local;
}

/**
 * @brief Exchange two positions in a vehicle paths
 *
 * @param problem
 * @param vehicle_paths
 * @param path
 * @param first_position
 * @param second_position
 */
void VrpIntraRouteExchange::ExchangePositions(const VrpProblem& problem,
                                              VehiclesPaths& vehicle_paths,
                                              std::size_t path,
                                              std::size_t first_position,
                                              std::size_t second_position) {
  ClientInfo first_client{vehicle_paths[path][first_position]};
  ClientInfo second_client{vehicle_paths[path][second_position]};

  vehicle_paths[path][first_position + 1].SetComeFrom(second_client.GetId());
  vehicle_paths[path][first_position + 1].SetDistance(
      problem.GetDistanceMatrix()[second_client.GetId()]
                                 [vehicle_paths[path][first_position + 1]
                                      .GetId()]);
  vehicle_paths[path][first_position].SetId(second_client.GetId());
  vehicle_paths[path][first_position].SetDistance(
      problem.GetDistanceMatrix()[first_client.GetComeFrom()]
                                 [second_client.GetId()]);

  vehicle_paths[path][second_position + 1].SetComeFrom(first_client.GetId());
  vehicle_paths[path][second_position + 1].SetDistance(
      problem.GetDistanceMatrix()[first_client.GetId()]
                                 [vehicle_paths[path][second_position + 1]
                                      .GetId()]);
  vehicle_paths[path][second_position].SetId(first_client.GetId());
  vehicle_paths[path][second_position].SetDistance(
      problem.GetDistanceMatrix()[second_client.GetComeFrom()]
                                 [first_client.GetId()]);
}

}  // namespace daa
