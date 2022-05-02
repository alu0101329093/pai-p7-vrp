#include "vrp/vrp_intra_route_reinsert.h"

namespace daa {

VrpIntraRouteReinsert::VrpIntraRouteReinsert() {}

/**
 * @brief Execute the local search by reinsert intra route
 *
 * @param problem
 * @param solution
 * @return VrpSolution
 */
VrpSolution VrpIntraRouteReinsert::Execute(const VrpProblem& problem,
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
          for (std::size_t j = 1; j < local_paths[path].size() - 1; ++j) {
            if (j == i || j == i - 1) continue;
            VehiclesPaths current_paths{local_paths};
            InsertPosition(problem, current_paths, path, i, j);
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
 * @param path
 * @param first_position
 * @param second_position
 */
void VrpIntraRouteReinsert::InsertPosition(const VrpProblem& problem,
                                           VehiclesPaths& vehicle_paths,
                                           std::size_t path,
                                           std::size_t first_position,
                                           std::size_t second_position) {
  ClientInfo client{vehicle_paths[path][first_position]};

  vehicle_paths[path][first_position + 1].SetComeFrom(client.GetComeFrom());
  vehicle_paths[path][first_position + 1].SetDistance(
      problem.GetDistanceMatrix()[client.GetComeFrom()]
                                 [vehicle_paths[path][first_position + 1]
                                      .GetId()]);
  vehicle_paths[path].erase(vehicle_paths[path].begin() + first_position);

  client.SetComeFrom(vehicle_paths[path][second_position].GetComeFrom());
  client.SetDistance(
      problem.GetDistanceMatrix()[client.GetComeFrom()][client.GetId()]);
  vehicle_paths[path].insert(vehicle_paths[path].begin() + second_position,
                             client);
  vehicle_paths[path][second_position].SetComeFrom(client.GetComeFrom());
  vehicle_paths[path][second_position].SetDistance(client.GetDistance());
  vehicle_paths[path][second_position + 1].SetComeFrom(client.GetId());
  vehicle_paths[path][second_position + 1].SetDistance(
      problem.GetDistanceMatrix()
          [client.GetId()][vehicle_paths[path][second_position + 1].GetId()]);
}

}  // namespace daa
