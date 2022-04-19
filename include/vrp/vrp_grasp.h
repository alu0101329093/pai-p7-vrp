#ifndef P7VRP_VRP_VRP_GRASP_H_
#define P7VRP_VRP_VRP_GRASP_H_

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <set>
#include <vector>

#include "vrp/client_info.h"
#include "vrp/vrp_grasp_solution.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

typedef std::set<std::size_t> ClientsSet;

typedef std::priority_queue<ClientInfo, std::vector<ClientInfo>,
                            std::greater<ClientInfo>>
    ClientsQueue;

class VrpGrasp {
 public:
  VrpGraspSolution Solve(const VrpProblem& problem, std::size_t iterations,
                         std::size_t random_solutions_amount,
                         std::size_t max_unchanged_iterations);

 private:
  ClientsSet GenerateClientSet(const VrpProblem& problem);

  std::set<ClientInfo> GetClientsBestOptions(const VrpProblem& problem,
                                             const ClientsSet& clients_set,
                                             const ClientsSet& current_clients,
                                             std::size_t amount);

  ClientInfo GetRandomOption(const std::set<ClientInfo>& options);

  VrpSolution SetInitialPath(const VrpProblem& problem,
                             std::size_t random_solutions_amount,
                             ClientsSet& clients_set);

  VrpSolution SolveStartedGreedy(const VrpProblem& problem,
                                 const VrpSolution& partial_solution,
                                 std::size_t random_solutions_amount,
                                 ClientsSet& clients_set);
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_GRASP_H_