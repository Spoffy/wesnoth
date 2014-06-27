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

#include "umcd/protocol/server/error_sender.hpp"
//#include "umcd/protocol/make_header.hpp"
//#include "umcd/protocol/server/close_on_error.hpp"
#include "umcd/protocol/server/special_packet.hpp"
#include "umcd/server/default_transfer_observer.hpp"
#include "umcd/logger/asio_logger.hpp"
#include "config.hpp"

#include <neev/buffer/prefixed_buffer.hpp>
#include <neev/network_transfer.hpp>
#include <neev/transfer_operation.hpp>

namespace umcd{

void async_send_error(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket, const std::string& error_message)
{
  using namespace neev;
  using buffer_type = prefixed32_buffer<send_op>;
	UMCD_LOG_IP_FUNCTION_TRACER(socket);
	config error_message_config = make_error_packet(error_message);
  std::string data_to_send = error_message_config.to_string();
  auto sender = make_transfer<buffer_type>(socket, default_transfer_observer(), std::move(data_to_send));
  sender->async_transfer();
}

void async_send_error(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket, const boost::system::error_condition& error, const std::string& extra_msg)
{
	UMCD_LOG_IP_FUNCTION_TRACER(socket);
	async_send_error(socket, error.message() + extra_msg);
}
} // namespace umcd
