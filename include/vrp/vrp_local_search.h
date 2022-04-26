#ifndef P7VRP_VRP_VRP_LOCAL_SEARCH_H_
#define P7VRP_VRP_VRP_LOCAL_SEARCH_H_

#include "vrp/vrp_solution.h"

namespace daa {

class VrpLocalSearch {
 public:
  virtual VrpSolution Execute(const VrpProblem& problem,
                              const VrpSolution& solution) = 0;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_LOCAL_SEARCH_H_