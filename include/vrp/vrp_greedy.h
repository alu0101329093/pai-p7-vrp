#ifndef P7VRP_VRP_VRP_GREEDY_H_
#define P7VRP_VRP_VRP_GREEDY_H_

#include <limits>
#include <queue>
#include <vector>

#include "vrp/client_info.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

class VrpGreedy {
 public:
  VrpGreedy();

  VrpSolution Solve(const VrpProblem& problem);

 private:
  std::priority_queue<ClientInfo, std::vector<ClientInfo>,
                      std::greater<ClientInfo>>
  GenerateClientList(const VrpProblem& problem);
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_GREEDY_H_
