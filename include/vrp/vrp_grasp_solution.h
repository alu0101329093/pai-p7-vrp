#ifndef P7VRP_VRP_VRP_GRASP_SOLUTION_H_
#define P7VRP_VRP_VRP_GRASP_SOLUTION_H_

#include <vector>

#include "vrp/vrp_solution.h"

namespace daa {

class VrpGraspSolution {
 public:
  VrpGraspSolution(std::vector<VrpSolution> solutions_history,
                   std::size_t best_solution);

  inline const std::vector<VrpSolution>& GetSolutionsHistory() const {
    return solutions_history_;
  }
  inline void SetSolutionsHistory(
      const std::vector<VrpSolution>& solutions_history) {
    solutions_history_ = solutions_history;
  }
  inline VrpSolution GetBestSolution() const {
    return solutions_history_[best_solution_];
  }
  inline void SetBestSolution(std::size_t index) { best_solution_ = index; }

 private:
  std::vector<VrpSolution> solutions_history_;
  std::size_t best_solution_;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_GRASP_SOLUTION_H_