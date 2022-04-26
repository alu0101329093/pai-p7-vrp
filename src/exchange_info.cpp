#include "vrp/exchange_info.h"

namespace daa {

ExchangeInfo::ExchangeInfo(const ClientInfo& first_client,
                           const ClientInfo& second_client,
                           std::size_t first_position,
                           std::size_t second_position, std::size_t first_route,
                           std::size_t second_route)
    : first_client_{first_client},
      second_client_{second_client},
      first_position_{first_position},
      second_position_{second_position},
      first_route_{first_route},
      second_route_{second_route} {}

}  // namespace daa
