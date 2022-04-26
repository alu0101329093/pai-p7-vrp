#ifndef P7VRP_VRP_VRP_GRASP_OPTIONS_H_
#define P7VRP_VRP_VRP_GRASP_OPTIONS_H_

#include <cstdlib>

#include "vrp/vrp_options.h"

namespace daa {

class VrpGraspOptions : public VrpOptions {
 public:
  VrpGraspOptions(std::size_t iterations, std::size_t random_solutions_amount,
                  std::size_t max_unchanged_iterations);
  virtual ~VrpGraspOptions() override;

  inline std::size_t GetIterations() const { return iterations_; }
  inline void SetIterations(std::size_t iterations) {
    iterations_ = iterations;
  }

  inline std::size_t GetRandomSolutionsAmount() const {
    return random_solutions_amount_;
  }
  inline void SetRandomSolutionsAmount(std::size_t random_solutions_amount) {
    random_solutions_amount_ = random_solutions_amount;
  }

  inline std::size_t GetMaxUnchangedIterations() const {
    return max_unchanged_iterations_;
  }
  inline void SetMaxUnchangedIterations(std::size_t max_unchanged_iterations) {
    max_unchanged_iterations_ = max_unchanged_iterations;
  }

 private:
  std::size_t iterations_;
  std::size_t random_solutions_amount_;
  std::size_t max_unchanged_iterations_;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_GRASP_OPTIONS_H_