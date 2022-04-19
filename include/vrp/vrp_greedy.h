#ifndef P7VRP_VRP_VRP_GREEDY_H_
#define P7VRP_VRP_VRP_GREEDY_H_

#include <limits>
#include <queue>
#include <set>
#include <vector>

#include "vrp/client_info.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

typedef std::set<std::size_t> ClientsSet;

typedef std::priority_queue<ClientInfo, std::vector<ClientInfo>,
                            std::greater<ClientInfo>>
    ClientsQueue;

class VrpGreedy {
 public:
  VrpGreedy();

  VrpSolution Solve(const VrpProblem& problem);

 private:
  std::priority_queue<ClientInfo, std::vector<ClientInfo>,
                      std::greater<ClientInfo>>
  GenerateCliensToBaseQueue(const VrpProblem& problem);

  VehiclesPaths SetReturnPaths(const VrpProblem& problem,
                               const VehiclesPaths& vehicle_paths);

  ClientsSet GenerateClientsSet(const VrpProblem& problem);

  ClientInfo GetBestOption(const VrpProblem& problem, ClientsSet clients_set,
                           const VehiclesPaths& vehicles_paths);
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_GREEDY_H_
