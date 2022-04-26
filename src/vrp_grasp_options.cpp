#include "vrp/vrp_grasp_options.h"

namespace daa {

VrpGraspOptions::VrpGraspOptions(std::size_t iterations,
                                 std::size_t random_solutions_amount,
                                 std::size_t max_unchanged_iterations,
                                 VrpLocalSearch* local_search)
    : iterations_{iterations},
      random_solutions_amount_{random_solutions_amount},
      max_unchanged_iterations_{max_unchanged_iterations},
      local_search_{local_search} {}

VrpGraspOptions::~VrpGraspOptions() {}

}  // namespace daa
