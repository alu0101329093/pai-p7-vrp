#ifndef P7VRP_VRP_VRP_INTRA_ROUTE_EXCHANGE_H_
#define P7VRP_VRP_VRP_INTRA_ROUTE_EXCHANGE_H_

#include <cstdlib>

#include "vrp/client_info.h"
#include "vrp/vrp_local_search.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

class VrpIntraRouteExchange : public VrpLocalSearch {
 public:
  VrpIntraRouteExchange();

  virtual VrpSolution Execute(const VrpProblem& problem,
                              const VrpSolution& solution) override;

 private:
  void ExchangePositions(const VrpProblem& problem,
                         VehiclesPaths& vehicle_paths, std::size_t path,
                         std::size_t first_position,
                         std::size_t second_position);
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_INTRA_ROUTE_EXCHANGE_H_