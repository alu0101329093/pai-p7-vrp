#ifndef P7VRP_VRP_VRP_ALGORITHM_H_
#define P7VRP_VRP_VRP_ALGORITHM_H_

#include <memory>

#include "vrp/vrp_options.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

class VrpAlgorithm {
 public:
  virtual VrpSolution Solve(const VrpProblem& problem,
                            const std::unique_ptr<VrpOptions>& options =
                                std::unique_ptr<VrpOptions>{}) = 0;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_ALGORITHM_H_