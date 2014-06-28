/*
	Copyright (C) 2013 by Pierre Talbot <ptalbot@hyc.io>
	Part of the Battle for Wesnoth Project http://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

/* @file A license can be requested for information or for acceptation before uploading/downloading an UMC.
* The license is not shipped with the Wesnoth client because this server can be re-used with different 
* licenses on other server than Wesnoth ones.
*/

#ifndef UMCD_REQUEST_LICENSE_ACTION_HPP
#define UMCD_REQUEST_LICENSE_ACTION_HPP

#include "umcd/actions/basic_action.hpp"
#include <neev/buffer/prefixed_buffer.hpp>
#include <neev/transfer_operation.hpp>

class config;

namespace umcd{

/** Send the license of the desired language or in english if not available.
* In the latter case, a warning is also sent.
*/
class request_license_action : 
  public basic_action_crtp<request_license_action>
{
public:
	using socket_type = boost::asio::ip::tcp::socket;
	using socket_ptr = std::shared_ptr<socket_type>;
  using send_buffer_type = neev::prefixed32_buffer<neev::send_op>;

	virtual void execute(const socket_ptr& socket, const config& request);
	virtual ~request_license_action();
};

} // namespace umcd
#endif // UMCD_REQUEST_LICENSE_ACTION_HPP
