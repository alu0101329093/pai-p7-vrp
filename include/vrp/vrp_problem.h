#ifndef P7VRP_VRP_VRP_PROBLEM_H_
#define P7VRP_VRP_VRP_PROBLEM_H_

#include <vector>

namespace daa {

typedef std::vector<std::vector<std::size_t>> DistanceMatrix;

class VrpProblem {
 public:
  VrpProblem();
  VrpProblem(const DistanceMatrix& distance_matrix, std::size_t clients_amount,
             std::size_t vehicles_amount);

  inline const DistanceMatrix& GetDistanceMatrix() const {
    return distance_matrix_;
  }
  inline void SetDistanceMatrix(const DistanceMatrix& distance_matrix) {
    distance_matrix_ = distance_matrix;
  }
  inline std::size_t GetClientsAmount() const { return clients_amount_; }
  inline void SetClientsAmount(std::size_t clients_amount) {
    clients_amount_ = clients_amount;
  }
  inline std::size_t GetVehiclesAmount() const { return vehicles_amount_; }
  inline void SetVehiclesAmount(std::size_t vehicles_amount) {
    vehicles_amount_ = vehicles_amount;
  }

 private:
  DistanceMatrix distance_matrix_;
  std::size_t clients_amount_;
  std::size_t vehicles_amount_;
};

}  // namespace daa

#endif  // P7VRP_VRP_VRP_PROBLEM_H_
