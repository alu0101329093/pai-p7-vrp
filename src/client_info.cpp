#include "vrp/client_info.h"

namespace daa {

ClientInfo::ClientInfo(std::size_t id, std::size_t distance,
                       std::size_t come_from)
    : id_{id}, distance_{distance}, come_from_{come_from} {}

}  // namespace daa
