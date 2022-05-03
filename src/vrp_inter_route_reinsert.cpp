#include "vrp/vrp_inter_route_reinsert.h"

namespace daa {

VrpInterRouteReinsert::VrpInterRouteReinsert() {}

/**
 * @brief Execute the local search by reinsert inter route
 *
 * @param problem
 * @param solution
 * @return VrpSolution
 */
VrpSolution VrpInterRouteReinsert::Execute(const VrpProblem& problem,
                                           const VrpSolution& solution) {
  DistanceMatrix distance_matrix = problem.GetDistanceMatrix();
  VrpSolution best_local{solution};
  VrpSolution old_local{solution};

  do {
    old_local = best_local;

    VrpSolution best_solution{best_local};
    VehiclesPaths local_paths{best_local.GetVehiclesPaths()};
    VrpSolution current_solution{best_local};
    for (std::size_t first_route = 0; first_route < local_paths.size();
         ++first_route) {
      for (std::size_t i = 1; i < local_paths[first_route].size() - 1; ++i) {
        for (std::size_t second_route = first_route;
             second_route < local_paths.size(); ++second_route) {
          for (std::size_t j = 1; j < local_paths[second_route].size() -
                                          (first_route == second_route ? 1 : 0);
               ++j) {
            if (first_route == second_route && (j == i || j == i - 1)) continue;
            VehiclesPaths current_paths{local_paths};
            InsertPosition(problem, current_paths, first_route, i, second_route,
                           j);
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
 * @brief Insert position in a vehicle paths
 *
 * @param problem
 * @param vehicle_paths
 * @param first_path
 * @param first_position
 * @param second_path
 * @param second_position
 */
void VrpInterRouteReinsert::InsertPosition(const VrpProblem& problem,
                                           VehiclesPaths& vehicle_paths,
                                           std::size_t first_path,
                                           std::size_t first_position,
                                           std::size_t second_path,
                                           std::size_t second_position) {
  ClientInfo client{vehicle_paths[first_path][first_position]};

  vehicle_paths[first_path][first_position + 1].SetComeFrom(
      client.GetComeFrom());
  vehicle_paths[first_path][first_position + 1].SetDistance(
      problem.GetDistanceMatrix()[client.GetComeFrom()]
                                 [vehicle_paths[first_path][first_position + 1]
                                      .GetId()]);
  vehicle_paths[first_path].erase(vehicle_paths[first_path].begin() +
                                  first_position);

  client.SetComeFrom(vehicle_paths[second_path][second_position].GetComeFrom());
  client.SetDistance(
      problem.GetDistanceMatrix()[client.GetComeFrom()][client.GetId()]);
  vehicle_paths[second_path].insert(
      vehicle_paths[second_path].begin() + second_position, client);
  vehicle_paths[second_path][second_position].SetComeFrom(client.GetComeFrom());
  vehicle_paths[second_path][second_position].SetDistance(client.GetDistance());
  vehicle_paths[second_path][second_position + 1].SetComeFrom(client.GetId());
  vehicle_paths[second_path][second_position + 1].SetDistance(
      problem.GetDistanceMatrix()
          [client.GetId()]
          [vehicle_paths[second_path][second_position + 1].GetId()]);
}

}  // namespace daa
