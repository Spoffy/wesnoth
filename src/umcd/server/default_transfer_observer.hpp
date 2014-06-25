/*
	Copyright (C) 2014 by Pierre Talbot <ptalbot@hyc.io>
	Copyright (C) 2014 by Callum Spawforth  <spoffeh@gmail.com>
	Part of the Battle for Wesnoth Project http://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

#ifndef UMCD_DEFAULT_OBSERVER
#define UMCD_DEFAULT_OBSERVER

#include <neev/transfer_events.hpp>

namespace umcd {

class default_transfer_observer {
 public:
  using events_type = neev::events<neev::transfer_error>;

  void transfer_error(const boost::system::error_code&);
};
} //end umcd namespace
