#ifndef P7VRP_VRP_VRP_INTRA_ROUTE_EXCHANGE_H_
#define P7VRP_VRP_VRP_INTRA_ROUTE_EXCHANGE_H_

#include <cstdlib>

#include "vrp/client_info.h"
#include "vrp/exchange_info.h"
#include "vrp/vrp_local_search.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

class VrpRouteExchange : public VrpLocalSearch {
 public:
  enum Type { kIntra, kBetween };
  VrpRouteExchange(Type type = Type::kIntra);

  virtual VrpSolution Execute(const VrpProblem& problem,
                              const VrpSolution& solution) override;

 private:
  ExchangeInfo GetExchangeInfo(const VrpSolution& solution);
  Type type_;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_INTRA_ROUTE_EXCHANGE_H_