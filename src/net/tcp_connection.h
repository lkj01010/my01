//
//  tcp_connection.h
//  my01
//
//  Created by 林 科俊 on 15/7/4.
//  Copyright (c) 2015年 mid. All rights reserved.
//

#ifndef __my01__tcp_connection__
#define __my01__tcp_connection__

#include <stdio.h>
#include "common.h"

namespace net
{
	class tcp_connection;
	class message;

	typedef boost::shared_ptr<tcp_connection> tcp_connection_ptr;
	typedef boost::function < void(const tcp_connection_ptr&)> connection_callback;
	typedef boost::function < void(const tcp_connection_ptr&, const message&, boost::posix_time::ptime)> message_callback;
	typedef boost::function < void(const tcp_connection_ptr&)> write_complete_callback;

	
	class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
	{
	public:
		tcp_connection(boost::asio::io_service& io_service)
			: socket_(io_service)
			, strand_(io_service)
		{}

		boost::asio::ip::tcp::socket& socket(){ return socket_; }
		bool is_open() { return socket_.is_open(); }

		void start();

		//void set_tie(const boost::shared_ptr<void>& tie){
		//	tie_ = tie;
		//}

		void set_module(void* module){ module_ = module; }
		void* const module() const{ return module_; }

		void send(const std::string& data);


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
		/// Handle completion of a read operation.
		void handle_read(const boost::system::error_code& e,
			std::size_t bytes_transferred);

		/// Handle completion of a write operation.
		void handle_write(const boost::system::error_code& e, 
			const size_t size);

		void handle_send(const std::string& data);
	private:
		boost::asio::ip::tcp::socket socket_;
		boost::asio::io_service::strand strand_;
		/// Buffer for incoming data.
		boost::array<char, 8192> buffer_;


		//boost::shared_ptr<boost::any> tie_;	//Tie a object to this, and managed by this

		void *module_;

		connection_callback connection_callback_;
		message_callback message_callback_;
		write_complete_callback write_complete_callback_;
	};


}

#endif /* defined(__my01__tcp_connection__) */
