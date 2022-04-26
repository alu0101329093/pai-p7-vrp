#ifndef P7VRP_VRP_VRP_SOLVER_H_
#define P7VRP_VRP_VRP_SOLVER_H_

#include <memory>

#include "vrp/vrp_algorithm.h"
#include "vrp/vrp_grasp.h"
#include "vrp/vrp_greedy.h"
#include "vrp/vrp_options.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

class VrpSolver {
 public:
  enum class AlgorithmTypes { kGreedy, kGrasp };

  VrpSolver();

  VrpSolution Solve(const VrpProblem& problem,
                    const std::unique_ptr<VrpOptions>& options =
                        std::unique_ptr<VrpOptions>{});

  void SetAlgorithm(AlgorithmTypes type);

 private:
  std::unique_ptr<VrpAlgorithm> algorithm_;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_SOLVER_H_