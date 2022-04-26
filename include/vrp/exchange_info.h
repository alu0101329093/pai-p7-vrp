#ifndef P7VRP_VRP_EXCHANGE_INFO_H_
#define P7VRP_VRP_EXCHANGE_INFO_H_

#include <cstddef>

#include "vrp/client_info.h"

namespace daa {

class ExchangeInfo {
 public:
  ExchangeInfo(const ClientInfo& first_client, const ClientInfo& second_client,
               std::size_t first_position, std::size_t second_position,
               std::size_t route);

  inline const ClientInfo& GetFirstClient() const { return first_client_; }
  inline void SetFirstClient(const ClientInfo& first_client) {
    first_client_ = first_client;
  }

  inline const ClientInfo& GetSecondClient() const { return second_client_; }
  inline void SetSecondClient(const ClientInfo& second_client) {
    second_client_ = second_client;
  }

  inline std::size_t GetFirstPosition() const { return first_position_; }
  inline void SetFirstPosition(std::size_t first_position) {
    first_position_ = first_position;
  }

  inline std::size_t GetSecondPosition() const { return second_position_; }
  inline void SetSecondPosition(std::size_t second_position) {
    second_position_ = second_position;
  }

  inline std::size_t GetRoute() const { return route_; }
  inline void SetRoute(std::size_t route) { route_ = route; }

 private:
  ClientInfo first_client_;
  ClientInfo second_client_;
  std::size_t first_position_;
  std::size_t second_position_;
  std::size_t route_;
};

}  // namespace daa

#endif  // P7VRP_VRP_EXCHANGE_INFO_H_
