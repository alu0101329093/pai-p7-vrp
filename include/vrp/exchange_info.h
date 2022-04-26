#ifndef P7VRP_VRP_EXCHANGE_INFO_H_
#define P7VRP_VRP_EXCHANGE_INFO_H_

#include <cstddef>

#include "vrp/client_info.h"

namespace daa {

class ExchangeInfo {
 public:
  ExchangeInfo(const ClientInfo& first_client, const ClientInfo& second_client,
               std::size_t first_position, std::size_t second_position,
               std::size_t first_route, std::size_t second_route);

  inline const ClientInfo& GetFirstClient() const { return first_client_; }
  inline void SetFirstClient(const ClientInfo& client) {
    first_client_ = client;
  }

  inline const ClientInfo& GetSecondClient() const { return second_client_; }
  inline void SetSecondClient(const ClientInfo& client) {
    second_client_ = client;
  }

  inline std::size_t GetFirstPosition() const { return first_position_; }
  inline void SetFirstPosition(std::size_t position) {
    first_position_ = position;
  }

  inline std::size_t GetSecondPosition() const { return second_position_; }
  inline void SetSecondPosition(std::size_t position) {
    second_position_ = position;
  }

  inline std::size_t GetFirstRoute() const { return first_route_; }
  inline void SetFirstRoute(std::size_t route) { first_route_ = route; }

  inline std::size_t GetSecondRoute() const { return second_route_; }
  inline void SetSecondRoute(std::size_t route) { second_route_ = route; }

 private:
  ClientInfo first_client_;
  ClientInfo second_client_;
  std::size_t first_position_;
  std::size_t second_position_;
  std::size_t first_route_;
  std::size_t second_route_;
};

}  // namespace daa

#endif  // P7VRP_VRP_EXCHANGE_INFO_H_
