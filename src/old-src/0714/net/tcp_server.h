#pragma once

#include "common.h"
#include "tcp_connection.h"

using boost::asio::ip::tcp;

namespace net
{
	class tcp_server
	{
	public:
		tcp_server();
		~tcp_server();


		const std::string& hostport() const { return hostport_; }
		const std::string& name() const { return name_; }

	private:
		typedef std::map<std::string, tcp_connection_ptr> tcp_connection_map;

		boost::asio::io_service& ios_;
		tcp::acceptor acceptor_;



		tcp_connection_map conns_;
		const std::string hostport_;
		const std::string name_;
		int next_conn_id_;
	};

}