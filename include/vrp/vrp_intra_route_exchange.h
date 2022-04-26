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
  virtual VrpSolution Execute(const VrpProblem& problem,
                              const VrpSolution& solution) override;

 private:
  struct ExchangeInfo {
    
  };

  ExchangeInfo GetClientsToExchange();
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_INTRA_ROUTE_EXCHANGE_H_