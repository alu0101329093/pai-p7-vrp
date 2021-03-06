#include "main.h"

int main(int argc, char* argv[]) {
  std::string path{argv[1]};
  // daa::VrpProblem problem{daa::ReadInfoFromFile(argv[1])};
  daa::VrpSolver solver{};
  std::cout << "|  FileName  |  Algorithm  |    Cost    | Time in ms |\n";
  for (const auto& entry :
       std::filesystem::directory_iterator{std::filesystem::path{path}}) {
    daa::VrpProblem problem{daa::ReadInfoFromFile(entry.path().string())};
    std::cout << "| " << entry.path().string() << " | ";
    std::cout << "  Greedy   | ";
    solver.SetAlgorithm(daa::VrpSolver::AlgorithmTypes::kGreedy);
    auto greedy_start_time = std::chrono::steady_clock::now();
    daa::VrpSolution greedy_solution{solver.Solve(problem)};
    auto greedy_actual_time = std::chrono::steady_clock::now();
    auto greedy_execution_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            greedy_actual_time - greedy_start_time);
    std::cout << "   " << greedy_solution.GetPathsDistanceSum() << "   | ";
    std::cout << "   " << greedy_execution_time.count() << "ms   | \n";

    std::cout << "| " << entry.path().string() << " | ";
    std::cout << "   Grasp    | ";
    solver.SetAlgorithm(daa::VrpSolver::AlgorithmTypes::kGrasp);
    const auto grasp_start_time = std::chrono::steady_clock::now();
    daa::VrpSolution grasp_solution{solver.Solve(
        problem, std::make_unique<daa::VrpGraspOptions>(
                     1000, 3, 100, new daa::VrpInterRouteExchange))};
    auto grasp_actual_time = std::chrono::steady_clock::now();
    auto grasp_execution_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            grasp_actual_time - grasp_start_time);
    std::cout << "   " << grasp_solution.GetPathsDistanceSum() << "   | ";
    std::cout << "   " << grasp_execution_time.count() << "ms   | \n";

    std::cout << "| " << entry.path().string() << " | ";
    std::cout << "   Gvns    | ";
    solver.SetAlgorithm(daa::VrpSolver::AlgorithmTypes::kGvns);
    const auto gvns_start_time = std::chrono::steady_clock::now();
    daa::VrpSolution gvns_solution{
        solver.Solve(problem, std::make_unique<daa::VrpGvnsOptions>(100))};
    auto gvns_actual_time = std::chrono::steady_clock::now();
    auto gvns_execution_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(gvns_actual_time -
                                                              gvns_start_time);
    std::cout << "   " << gvns_solution.GetPathsDistanceSum() << "   | ";
    std::cout << "   " << gvns_execution_time.count() << "ms   | \n";
  }
  // std::cout << greedy_solution << std::endl;

  // solver.SetAlgorithm(daa::VrpSolver::AlgorithmTypes::kGrasp);
  // daa::VrpSolution grasp_solution{
  //     solver.Solve(problem, std::make_unique<daa::VrpGraspOptions>(
  //                               1000, 3, 500, new
  //                               daa::VrpInterRouteReinsert))};

  // std::cout << grasp_solution << std::endl;

  // solver.SetAlgorithm(daa::VrpSolver::AlgorithmTypes::kGvns);
  // daa::VrpSolution gvns_solution{
  //     solver.Solve(problem, std::make_unique<daa::VrpGvnsOptions>(100))};

  // std::cout << gvns_solution << std::endl;

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
