#ifndef P7VRP_VRP_VRP_GVNS_OPTIONS_H_
#define P7VRP_VRP_VRP_GVNS_OPTIONS_H_

#include <cstdlib>

#include "vrp/vrp_options.h"

namespace daa {

class VrpGvnsOptions : public VrpOptions {
 public:
  VrpGvnsOptions(std::size_t iterations);
  virtual ~VrpGvnsOptions() override;

  inline std::size_t GetIterations() const { return iterations_; }
  inline void SetIterations(std::size_t iterations) {
    iterations_ = iterations;
  }

 private:
  std::size_t iterations_;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_GVNS_OPTIONS_H_