#ifndef P7VRP_VRP_VRP_INTRA_ROUTE_REINSERT_H_
#define P7VRP_VRP_VRP_INTRA_ROUTE_REINSERT_H_

#include <cstdlib>

#include "vrp/client_info.h"
#include "vrp/vrp_local_search.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

class VrpIntraRouteReinsert : public VrpLocalSearch {
 public:
  VrpIntraRouteReinsert();

  virtual VrpSolution Execute(const VrpProblem& problem,
                              const VrpSolution& solution) override;

 private:
  void InsertPosition(const VrpProblem& problem,
                         VehiclesPaths& vehicle_paths, std::size_t path,
                         std::size_t first_position,
                         std::size_t second_position);
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_INTRA_ROUTE_REINSERT_H_