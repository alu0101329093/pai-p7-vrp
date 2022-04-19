#include "vrp/vrp_grasp_solution.h"

namespace daa {

VrpGraspSolution::VrpGraspSolution(std::vector<VrpSolution> solutions_history,
                                   std::size_t best_solution)
    : solutions_history_{solutions_history}, best_solution_{best_solution} {}

}  // namespace daa
