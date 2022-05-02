#include "main.h"

int main(int argc, char* argv[]) {
  daa::VrpProblem problem{daa::ReadInfoFromFile(argv[1])};
  daa::VrpSolver solver{};
  solver.SetAlgorithm(daa::VrpSolver::AlgorithmTypes::kGreedy);
  daa::VrpSolution greedy_solution{solver.Solve(problem)};
  std::cout << greedy_solution << std::endl;
  solver.SetAlgorithm(daa::VrpSolver::AlgorithmTypes::kGrasp);
  daa::VrpSolution grasp_solution{
      solver.Solve(problem, std::make_unique<daa::VrpGraspOptions>(
                                1000, 3, 500, new daa::VrpInterRouteExchange))};
  std::cout << grasp_solution << std::endl;

  return EXIT_SUCCESS;
}

namespace daa {

/**
 * @brief Read problem info from a file
 *
 * @param file_name
 * @return VrpProblem
 */
VrpProblem ReadInfoFromFile(const std::string& file_name) {
  std::ifstream input_file{file_name};
  VrpProblem problem{};
  std::size_t amount{};
  std::string text{};
  input_file >> text >> amount;
  problem.SetClientsAmount(amount);
  input_file >> text >> amount;
  problem.SetVehiclesAmount(amount);
  input_file >> text;

  amount = problem.GetClientsAmount() + 1;
  DistanceMatrix distance_matrix{amount, std::vector<std::size_t>{}};
  std::size_t distance{};
  for (std::size_t i = 0; i < amount; ++i) {
    for (std::size_t j = 0; j < amount; ++j) {
      input_file >> distance;
      distance_matrix[i].push_back(distance);
    }
  }
  problem.SetDistanceMatrix(distance_matrix);

  return problem;
}

}  // namespace daa
