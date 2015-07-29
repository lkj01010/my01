#pragma once

#include "com/common.h"
#include "net/tcp_connection.h"
#include "net/io_service_pool.hpp"

using boost::asio::ip::tcp;

namespace net
{
	class tcp_server
		: private boost::noncopyable
	{
	public:
		/// Construct the server to listen on the specified TCP address and port, and
		/// serve up files from the given directory.
		explicit tcp_server(const std::string& address, const std::string& port,
			std::size_t io_service_pool_size);
		
		/// Run the server's io_service loop.
		void run();

		void set_connection_callback(const connection_callback& cb){
			connection_callback_ = cb;
		}

		void set_message_callback(const message_callback& cb){
			message_callback_ = cb;
		}
		void set_write_complete_callback(const write_complete_callback& cb){
			write_complete_callback_ = cb;
		}

	private:
		void start_accept();

		void handle_accept(const boost::system::error_code& e);

		// can invoke from master thread or conn thread both
		void remove_connection(const tcp_connection_ptr& conn);
		// do something like removing conn handler from server, if have.
		void handle_remove_connection(const tcp_connection_ptr& conn);

		void handle_stop();

		io_service_pool io_service_pool_;
		boost::asio::signal_set signals_;
		boost::asio::ip::tcp::acceptor acceptor_;
		tcp_connection_ptr new_connection_;

		boost::asio::io_service& io_master_;
		boost::asio::io_service::strand strand_;

		connection_callback connection_callback_;
		message_callback message_callback_;
		write_complete_callback write_complete_callback_;

		int next_conn_id_;

	};

}