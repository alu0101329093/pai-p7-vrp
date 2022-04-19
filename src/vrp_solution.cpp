#include "vrp/vrp_solution.h"

namespace daa {

VrpSolution::VrpSolution(const VehiclesPaths& vehicles_paths)
    : vehicles_paths_{vehicles_paths} {}

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
