#ifndef P7VRP_VRP_VRP_GVNS_H_
#define P7VRP_VRP_VRP_GVNS_H_

#include <limits>
#include <memory>
#include <vector>

#include "vrp/vrp_algorithm.h"
#include "vrp/vrp_grasp.h"
#include "vrp/vrp_gvns_options.h"
#include "vrp/vrp_inter_route_exchange.h"
#include "vrp/vrp_inter_route_reinsert.h"
#include "vrp/vrp_intra_route_exchange.h"
#include "vrp/vrp_intra_route_reinsert.h"
#include "vrp/vrp_options.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"
#include "vrp/vrp_solver.h"

namespace daa {

class VrpGvns : public VrpAlgorithm {
 public:
  VrpGvns();

  virtual VrpSolution Solve(const VrpProblem& problem,
                            const std::unique_ptr<VrpOptions>& options =
                                std::unique_ptr<VrpOptions>{}) override;

 private:
  VrpSolution Gvns(const VrpProblem& problem, const VrpSolution& solution);
  VrpSolution Shaking(const VrpProblem& problem, std::size_t amount,
                      const VrpSolution& solution);
  void InsertPosition(const VrpProblem& problem, VehiclesPaths& vehicle_paths,
                      std::size_t first_path, std::size_t first_position,
                      std::size_t second_path, std::size_t second_position);

  std::vector<std::unique_ptr<VrpLocalSearch>> local_searchs_;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_GVNS_H_