#ifndef UMCD_DEFAULT_OBSERVER
#define UMCD_DEFAULT_OBSERVER

#include <neev/transfer_events.hpp>

namespace umcd {

class default_transfer_observer {
 public:
  using events_type = neev::events<neev::transfer_error>;

  void transfer_error(const boost::system::error_code&);
};
