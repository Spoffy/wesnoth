/*
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

/** @file Dispatch incoming request on the good action. An action is a class
* that handles a specific request.
*/

#ifndef UMCD_ACTION_DISPATCHER_HPP
#define UMCD_ACTION_DISPATCHER_HPP

#include "umcd/server/generic_factory.hpp"
#include "umcd/actions/basic_action.hpp"
#include "config.hpp"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <neev/buffer/prefixed_buffer.hpp>

namespace umcd{

class action_dispatcher : public boost::enable_shared_from_this<action_dispatcher>
{
public:
	using action_ptr = std::shared_ptr<basic_action>;
	using socket_type = boost::asio::ip::tcp::socket;
	using socket_ptr = std::shared_ptr<socket_type>;

  using receive_buffer_type = neev::prefixed16_buffer<neev::receive_op>;
  using events_type = neev::events<neev::transfer_complete>;
  using data_type = receive_buffer_type::type::data_type;

private:
	using action_factory_type = generic_factory<basic_action>;

public:
	action_dispatcher(const socket_ptr& socket)
	: socket_(socket)
	{}

	/** Before starting to dispatch request, we must read it first.
	* We read it in this class because the data will only be used here.
	* The dispatch will be automatic after the reading.
	*/
	void async_read_request();

  void transfer_complete(const data_type& data);

private:
	/** Dispatch a successful read request on the good action.
	*/
	void dispatch();

	socket_ptr socket_;
	config received_request_;

	/** Boilerplate code that initialized the action factory.
	* This factory maps request name to action object.
	*/
	static action_factory_type action_factory;
 	struct action_factory_initializer
	{
		action_factory_initializer();
	};
	static action_factory_initializer action_init;
};

} // namespace umcd
#endif // UMCD_ACTION_DISPATCHER_HPP
