#include "umcd_server.hpp"
#include "umcd/logger/asio_logger.hpp"
#include "umcd/protocol/server/entry_point.hpp"

void umcd_server::start_success(const endpoint_type& endpoint) const
{
  UMCD_LOG(info) << "UMCD started on " << endpoint << "\n";
}

void umcd_server::start_failure() const
{
  UMCD_LOG(error) << 
  "Unable to start UMCD server. Check network interfaces"
  << "\n";
}

void umcd_server::new_client(const socket_ptr& socket) const
{
  umcd::protocol_entry_point(socket);
}


