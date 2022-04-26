#include "vrp/vrp_grasp_options.h"

namespace daa {

VrpGraspOptions::VrpGraspOptions(std::size_t iterations,
                                 std::size_t random_solutions_amount,
                                 std::size_t max_unchanged_iterations)
    : iterations_{iterations},
      random_solutions_amount_{random_solutions_amount},
      max_unchanged_iterations_{max_unchanged_iterations} {}

VrpGraspOptions::~VrpGraspOptions() {}

}  // namespace daa
