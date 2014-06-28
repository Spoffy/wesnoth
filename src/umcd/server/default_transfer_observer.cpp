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

#include "default_transfer_observer.hpp"
#include "umcd/logger/asio_logger.hpp"

void umcd::default_transfer_observer::transfer_error( const boost::system::error_code& error ) {
  UMCD_LOG(error) << "Transfer error: " << error.message();
}
  
