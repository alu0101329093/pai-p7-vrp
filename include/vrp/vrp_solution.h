#ifndef P7VRP_VRP_VRP_SOLUTION_H_
#define P7VRP_VRP_VRP_SOLUTION_H_

#include <ostream>
#include <string>
#include <vector>

#include "vrp/client_info.h"

namespace daa {

typedef std::vector<std::vector<ClientInfo>> VehiclesPaths;

class VrpSolution {
 public:
  VrpSolution(const VehiclesPaths& vehicles_paths);

  inline const VehiclesPaths GetVehiclesPaths() const {
    return vehicles_paths_;
  }
  inline void SetVehiclesPaths(const VehiclesPaths& vehicles_paths) {
    vehicles_paths_ = vehicles_paths;
  }

  friend std::ostream& operator<<(std::ostream& os,
                                  const VrpSolution& solution) {
    os << "Vehicles:\n";
    for (std::size_t i = 0; i < solution.vehicles_paths_.size(); ++i) {
      os << i << ". 0 -> ";
      std::size_t path_size{solution.vehicles_paths_[i].size()};
      std::size_t path_distance_sum{};
      for (std::size_t j = 0; j < path_size; ++j) {
        path_distance_sum += solution.vehicles_paths_[i][j].GetDistance();
        os << solution.vehicles_paths_[i][j].GetId() << " : "
           << solution.vehicles_paths_[i][j].GetDistance()
           << (j == path_size - 1
                   ? (" = " + std::to_string(path_distance_sum) + "\n")
                   : " -> ");
      }
    }
    return os;
  }

 private:
  VehiclesPaths vehicles_paths_;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_SOLUTION_H_