#include "vrp/vrp_solution.h"

namespace daa {

/**
 * @brief Construct a new Vrp Solution:: Vrp Solution object
 *
 * @param vehicles_paths
 */
VrpSolution::VrpSolution(const VehiclesPaths& vehicles_paths)
    : vehicles_paths_{vehicles_paths} {}

/**
 * @brief Get the sum of every path distance
 *
 * @return std::size_t
 */
std::size_t VrpSolution::GetPathsDistanceSum() const {
  std::size_t sum{};
  for (auto path : vehicles_paths_) {
    for (auto client : path) {
      sum += client.GetDistance();
    }
  }
  return sum;
}

}  // namespace daa
