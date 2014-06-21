#ifndef UMCD_SERVER
#define UMCD_SERVER

#include<neev/traits/observer_traits.hpp>
#include<neev/server/server_events.hpp>

class umcd_server 
{
 public:
  using events_type = neev::events<
      neev::start_success,
      neev::start_failure,
      neev::new_client>;

  using socket_ptr = std::shared_ptr<boost::asio::ip::tcp::socket>;
  using endpoint_type = boost::asio::ip::tcp::endpoint;

  void start_success(const endpoint_type&) const;
  void start_failure() const;
  void new_client(const socket_ptr& socket) const;
};

#endif
