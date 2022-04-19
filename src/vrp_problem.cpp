#include "vrp/vrp_problem.h"

namespace daa {

VrpProblem::VrpProblem()
    : distance_matrix_{}, clients_amount_{}, vehicles_amount_{} {}

VrpProblem::VrpProblem(const DistanceMatrix& distance_matrix,
                       std::size_t clients_amount, std::size_t vehicles_amount)
    : distance_matrix_{distance_matrix},
      clients_amount_{clients_amount},
      vehicles_amount_{vehicles_amount} {}

}  // namespace daa
