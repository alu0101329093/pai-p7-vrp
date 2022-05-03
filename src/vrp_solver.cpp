#include "vrp/vrp_solver.h"

namespace daa {

VrpSolver::VrpSolver() : algorithm_{} {}

VrpSolution VrpSolver::Solve(const VrpProblem& problem,
                             const std::unique_ptr<VrpOptions>& options) {
  if (algorithm_) {
    return algorithm_->Solve(problem, options);
  }
}

void VrpSolver::SetAlgorithm(AlgorithmTypes type) {
  switch (type) {
    case AlgorithmTypes::kGreedy:
      algorithm_.reset(new VrpGreedy{});
      break;
    case AlgorithmTypes::kGrasp:
      algorithm_.reset(new VrpGrasp{});
      break;
    case AlgorithmTypes::kGvns:
      algorithm_.reset(new VrpGvns{});
      break;
    default:
      break;
  }
}

}  // namespace daa
