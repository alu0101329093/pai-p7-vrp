#include "vrp/vrp_gvns.h"

namespace daa {

/**
 * @brief Construct a new Vrp Gvns:: Vrp Gvns object
 *
 */
VrpGvns::VrpGvns() : local_searchs_{} {
  local_searchs_.emplace_back(new VrpInterRouteReinsert);
  local_searchs_.emplace_back(new VrpIntraRouteReinsert);
  local_searchs_.emplace_back(new VrpInterRouteExchange);
  local_searchs_.emplace_back(new VrpIntraRouteExchange);
}

/**
 * @brief Solve rvp by gvns
 *
 * @param problem
 * @param options
 * @return VrpSolution
 */
VrpSolution VrpGvns::Solve(const VrpProblem& problem,
                           const std::unique_ptr<VrpOptions>& options) {
  VrpGvnsOptions* parsedOptions =
      reinterpret_cast<VrpGvnsOptions*>(options.get());
  std::size_t iterations = parsedOptions->GetIterations();

  VrpSolver grasp{};
  grasp.SetAlgorithm(daa::VrpSolver::AlgorithmTypes::kGrasp);
  VrpSolution best_solution{grasp.Solve(
      problem, std::make_unique<VrpGraspOptions>(iterations, 3, iterations / 2,
                                                 new VrpInterRouteReinsert))};
  std::srand(std::time(nullptr));
  for (std::size_t i = 0; i < iterations; ++i) {
    VrpSolution current_solution{grasp.Solve(
        problem,
        std::make_unique<VrpGraspOptions>(iterations, 3, iterations / 2,
                                          new VrpInterRouteReinsert))};
    current_solution = Gvns(problem, current_solution);
    if (current_solution.GetPathsDistanceSum() <
        best_solution.GetPathsDistanceSum())
      best_solution = current_solution;
  }

  return best_solution;
}

/**
 * @brief Create gvns iteration solution
 *
 * @param problem
 * @param solution
 * @return VrpSolution
 */
VrpSolution VrpGvns::Gvns(const VrpProblem& problem,
                          const VrpSolution& solution) {
  VrpSolution best_solution{solution};
  const std::size_t max_jumps =
      static_cast<std::size_t>(problem.GetClientsAmount() * 0.2);
  std::size_t current_jump{};

  while (current_jump < max_jumps) {
    VrpSolution shaking_solution{Shaking(problem, current_jump, best_solution)};
    std::size_t current_search{};
    while (current_search < local_searchs_.size()) {
      VrpSolution local_solution{
          local_searchs_[current_search]->Execute(problem, shaking_solution)};
      if (local_solution.GetPathsDistanceSum() <
          shaking_solution.GetPathsDistanceSum()) {
        shaking_solution = local_solution;
        current_search = 0;
      } else {
        ++current_search;
      }
    }
    if (shaking_solution.GetPathsDistanceSum() <
        best_solution.GetPathsDistanceSum()) {
      best_solution = shaking_solution;
      current_jump = 0;
    } else {
      ++current_jump;
    }
  }

  return best_solution;
}

/**
 * @brief Shake the current solution to near neighbor
 *
 * @param problem
 * @param amount
 * @param solution
 * @return VrpSolution
 */
VrpSolution VrpGvns::Shaking(const VrpProblem& problem, std::size_t amount,
                             const VrpSolution& solution) {
  VehiclesPaths vehicles_paths{solution.GetVehiclesPaths()};
  std::size_t old_path{SIZE_MAX};
  std::size_t old_position{SIZE_MAX};
  VrpInterRouteReinsert reinsert{};
  for (std::size_t i = 0; i < amount; ++i) {
    std::size_t first_path{std::rand() % vehicles_paths.size()};
    std::size_t first_position{
        std::rand() % (vehicles_paths[first_path].size() - 2) + 1};
    std::size_t second_path{std::rand() % vehicles_paths.size()};
    std::size_t second_position{
        std::rand() % (vehicles_paths[second_path].size() - 2) + 1};
    if (old_path == second_path && old_position == second_position) {
      --i;
      continue;
    }
    InsertPosition(problem, vehicles_paths, first_path, first_position,
                   second_path, second_position);
  }
  return VrpSolution{vehicles_paths};
}

/**
 * @brief Insert position in inter route
 *
 * @param problem
 * @param vehicle_paths
 * @param first_path
 * @param first_position
 * @param second_path
 * @param second_position
 */
void VrpGvns::InsertPosition(const VrpProblem& problem,
                             VehiclesPaths& vehicle_paths,
                             std::size_t first_path, std::size_t first_position,
                             std::size_t second_path,
                             std::size_t second_position) {
  std::size_t f_size{vehicle_paths[first_path].size()};
  std::size_t s_size{vehicle_paths[second_path].size()};
  ClientInfo client{vehicle_paths[first_path][first_position]};

  vehicle_paths[first_path][first_position + 1].SetComeFrom(
      client.GetComeFrom());
  vehicle_paths[first_path][first_position + 1].SetDistance(
      problem.GetDistanceMatrix()[client.GetComeFrom()]
                                 [vehicle_paths[first_path][first_position + 1]
                                      .GetId()]);
  vehicle_paths[first_path].erase(vehicle_paths[first_path].begin() +
                                  first_position);

  client.SetComeFrom(vehicle_paths[second_path][second_position].GetComeFrom());
  client.SetDistance(
      problem.GetDistanceMatrix()[client.GetComeFrom()][client.GetId()]);
  vehicle_paths[second_path].insert(
      vehicle_paths[second_path].begin() + second_position, client);
  vehicle_paths[second_path][second_position].SetComeFrom(client.GetComeFrom());
  vehicle_paths[second_path][second_position].SetDistance(client.GetDistance());
  vehicle_paths[second_path][second_position + 1].SetComeFrom(client.GetId());
  vehicle_paths[second_path][second_position + 1].SetDistance(
      problem.GetDistanceMatrix()
          [client.GetId()]
          [vehicle_paths[second_path][second_position + 1].GetId()]);
}

}  // namespace daa
