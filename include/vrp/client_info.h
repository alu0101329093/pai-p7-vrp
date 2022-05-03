#ifndef P7VRP_VRP_CLIENT_INFO_H_
#define P7VRP_VRP_CLIENT_INFO_H_

#include <cstddef>

namespace daa {

class ClientInfo {
 public:
  ClientInfo(std::size_t id, std::size_t distance, std::size_t come_from);

  inline std::size_t GetId() const { return id_; }
  inline void SetId(std::size_t id) { id_ = id; }

  inline std::size_t GetDistance() const { return distance_; }
  inline void SetDistance(std::size_t distance) { distance_ = distance; }

  inline std::size_t GetComeFrom() const { return come_from_; }
  inline void SetComeFrom(std::size_t come_from) { come_from_ = come_from; }

  friend bool operator<(const ClientInfo& first_client,
                        const ClientInfo& second_client) {
    return first_client.distance_ < second_client.distance_ ||
           (first_client.distance_ == second_client.distance_ &&
            first_client.id_ < second_client.id_) ||
           (first_client.distance_ == second_client.distance_ &&
            first_client.id_ == second_client.id_ &&
            first_client.come_from_ < second_client.come_from_);
  }
  friend bool operator>(const ClientInfo& first_client,
                        const ClientInfo& second_client) {
    return first_client.distance_ > second_client.distance_ ||
           (first_client.distance_ == second_client.distance_ &&
            first_client.id_ > second_client.id_) ||
           (first_client.distance_ == second_client.distance_ &&
            first_client.id_ == second_client.id_ &&
            first_client.come_from_ > second_client.come_from_);
  }

  friend bool operator==(const ClientInfo& first_client,
                         const ClientInfo& second_client) {
    return first_client.id_ == second_client.id_ &&
           first_client.distance_ == second_client.distance_ &&
           first_client.come_from_ == second_client.come_from_;
  }
  friend bool operator!=(const ClientInfo& first_client,
                         const ClientInfo& second_client) {
    return first_client.id_ != second_client.id_ ||
           first_client.distance_ != second_client.distance_ ||
           first_client.come_from_ != second_client.come_from_;
  }

 private:
  std::size_t id_;
  std::size_t distance_;
  std::size_t come_from_;
};

}  // namespace daa

#endif  // P7VRP_VRP_CLIENT_INFO_H_
