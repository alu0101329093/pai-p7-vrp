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
#include "vrp/vrp_algorithm.h"
#include "vrp/vrp_grasp_options.h"
#include "vrp/vrp_options.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

typedef std::set<std::size_t> ClientsSet;

typedef std::priority_queue<ClientInfo, std::vector<ClientInfo>,
                            std::greater<ClientInfo>>
    ClientsQueue;

struct GraspState {
  std::size_t best_solution_distance;
  std::size_t best_solution;
  std::size_t unchanged_iterations;
};

class VrpGrasp : public VrpAlgorithm {
 public:
  virtual VrpSolution Solve(const VrpProblem& problem,
                            const std::unique_ptr<VrpOptions>& options =
                                std::unique_ptr<VrpOptions>{}) override;

 private:
  VrpSolution ConstructionPhase(const VrpProblem& problem,
                                VrpGraspOptions* options);
  VrpSolution PostProcessing(const VrpProblem& problem,
                             const VrpSolution& solution,
                             VrpGraspOptions* options);

  ClientsSet GenerateClientSet(const VrpProblem& problem);

  std::set<ClientInfo> GetClientsBestOptions(const VrpProblem& problem,
                                             const ClientsSet& clients_set,
                                             const ClientsSet& current_clients,
                                             std::size_t amount);

  ClientInfo GetRandomOption(const std::set<ClientInfo>& options);

  VrpSolution SetInitialPath(const VrpProblem& problem,
                             std::size_t random_solutions_amount,
                             ClientsSet& clients_set);

  VrpSolution SolveStartedProblem(const VrpProblem& problem,
                                  const VrpSolution& partial_solution,
                                  std::size_t random_solutions_amount,
                                  ClientsSet& clients_set);

  VehiclesPaths SetReturnPaths(const VrpProblem& problem,
                               const VehiclesPaths& vehicles_paths);
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_GRASP_H_