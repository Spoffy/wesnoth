#include "default_transfer_observer.hpp"
#include "umcd/logger/asio_logger.hpp"

void umcd::default_transfer_observer::transfer_error( const ::boost::system::error_code& error ) {
  UMCD_LOG(error) << "Transfer error: " << error.message();
}
  
