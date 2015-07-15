//
//  tcp_connection.cpp
//  my01
//
//  Created by 林 科俊 on 15/7/4.
//  Copyright (c) 2015年 mid. All rights reserved.
//

#include "tcp_connection.h"
#include "message.h"

using namespace net;

using boost::asio::ip::tcp;
using namespace std;

void tcp_connection::start()
{
	connection_callback_(shared_from_this());

	socket_.async_read_some(boost::asio::buffer(buffer_),
		boost::bind(&tcp_connection::handle_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::handle_read(const boost::system::error_code& e,
	std::size_t bytes_transferred)
{
	if (!e)
	{
		message msg;
		msg.set_content(string(buffer_.begin(), buffer_.end()));
		message_callback_(shared_from_this(), msg, boost::posix_time::second_clock::local_time());

		bool result = false;
		

		if (result)
		{
			boost::asio::async_write(socket_, 
				boost::asio::buffer(""),
				boost::asio::transfer_at_least(0),
				boost::bind(&tcp_connection::handle_write, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			socket_.async_read_some(boost::asio::buffer(buffer_),
				boost::bind(&tcp_connection::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
	}

	// If an error occurs then no new asynchronous operations are started. This
	// means that all shared_ptr references to the connection object will
	// disappear and the object will be destroyed automatically after this
	// handler returns. The connection class's destructor closes the socket.
}

void tcp_connection::handle_write(const boost::system::error_code& e, const size_t size)
{
	if (!e)
	{
		// Initiate graceful connection closure.
		boost::system::error_code ignored_ec;
		//socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
	}

	// No new asynchronous operations are started. This means that all shared_ptr
	// references to the connection object will disappear and the object will be
	// destroyed automatically after this handler returns. The connection class's
	// destructor closes the socket.
}

void tcp_connection::send(const string& data)
{
	if (!is_open()) {
		return;
	}
	//string data = message.serialize_as_string();
	try
	{
		strand_.dispatch(
			boost::bind(
			&tcp_connection::handle_send,
			shared_from_this(),
			data
			)
			);
	}
	catch (const boost::bad_weak_ptr& e)
	{
		//LOG_DEBUG("net", "_strand.post: send_data, error:%s", e.what());
	};
}
void tcp_connection::handle_send(const std::string& data){
	boost::asio::async_write(
		socket_,
		boost::asio::buffer(data.c_str(), data.size()), boost::asio::transfer_at_least(data.size()),
		strand_.wrap(boost::bind(&tcp_connection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred))
		);
}
