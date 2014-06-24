/*
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

#include "umcd/protocol/server/action_dispatcher.hpp"

#include "umcd/actions/request_license_action.hpp"
#include "umcd/actions/request_umc_upload_action.hpp"
#include "umcd/protocol/make_header.hpp"
#include "umcd/protocol/server/close_on_error.hpp"
#include "umcd/protocol/server/error_sender.hpp"
#include "umcd/error.hpp"
#include "umcd/logger/asio_logger.hpp"
#include <boost/current_function.hpp>

namespace umcd{

action_dispatcher::action_factory_type action_dispatcher::action_factory;
action_dispatcher::action_factory_initializer action_dispatcher::action_init;

action_dispatcher::action_factory_initializer::action_factory_initializer()
{
	action_factory.register_product("request_license", std::make_shared<request_license_action>());
	action_factory.register_product("request_umc_upload", std::make_shared<request_umc_upload_action>());
}

void action_dispatcher::async_read_request()
{
  using namespace neev;
	UMCD_LOG_IP_FUNCTION_TRACER(socket_);
  auto receive_transfer = make_transfer<receive_buffer_type>(socket_, *this);
  receive_transfer->async_transfer();
}

//Refactor to remove header_data intermediary. Totally unnecessary.
void action_dispatcher::transfer_complete(const data_type& data) {
  UMCD_LOG_IP(debug, socket_) << "action_dispatcher received incoming data " << data;
  core::header_data header;
  header.metadata = data;
  received_request_ << header;
  dispatch();
}

void action_dispatcher::dispatch()
{
	UMCD_LOG_IP_FUNCTION_TRACER(socket_);
	try
	{
		// Retrieve request name.
		config::all_children_itors range = received_request_.all_children_range();
		if(range.first == range.second)
		{
		  UMCD_LOG_IP(warning, socket_) << "invalid request at " << BOOST_CURRENT_FUNCTION << " (Request name not found).";
			async_send_error(socket_, make_error_condition(invalid_packet_name));
		}
		else
		{
			const std::string& request_name = range.first->key;
			UMCD_LOG_IP(info, socket_) << "request name: " << request_name;
			UMCD_LOG_IP(trace, socket_) << "request header:\n" << received_request_;

			action_ptr action = action_factory.make_product(request_name);
			action->execute(socket_, received_request_);
		}
	}
	catch(const std::exception& e)
	{
		UMCD_LOG_IP(warning, socket_) << "invalid request at " << BOOST_CURRENT_FUNCTION << " (" << e.what() << ").";
		async_send_error(socket_, make_error_condition(invalid_packet));
	}
}

} // namespace umcd
