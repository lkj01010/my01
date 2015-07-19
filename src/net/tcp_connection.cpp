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

void net::default_connection_callback(const tcp_connection_ptr& conn)
{
	std::cout << "defaultConnectionCallback" << std::endl;
	// do not call conn->forceClose(), because some users want to register message callback only.
}

void net::default_message_callback(const tcp_connection_ptr&, const message&, boost::posix_time::ptime)
{
	
}

//----------------------------------------------------------------------

tcp_connection::tcp_connection(boost::asio::io_service& io_service)
	: ios_(io_service)
	, socket_(io_service)
	, strand_(io_service)
{}

void tcp_connection::connect_established()
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
    // is_open()??? NO !!! should not discard this. when client is close, you should still deal with their message！
    if (!e)
    {
        if (bytes_transferred > 0)
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
    }
    else{
        close();
        std::cerr << "tcp_connection closed. handle_read." << e.value() << e.message() << std::endl;
        
    }

	// If an error occurs then no new asynchronous operations are started. This
	// means that all shared_ptr references to the connection object will
	// disappear and the object will be destroyed automatically after this
	// handler returns. The connection class's destructor closes the socket.
}

void tcp_connection::handle_write(const boost::system::error_code& e, const size_t size)
{
    // there would be much accumulated commands before socket is closed. When this occurs, discard them.
    if (is_open()){
        if (!e)
        {
            // Initiate graceful connection closure.
            boost::system::error_code ignored_ec;
            //socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }
        else{
            close();
            std::cerr << "tcp_connection closed. handle_write." << e.value() << e.message() << std::endl;
        }
    }
}

void tcp_connection::close(){
	// remove self in parent. 
	// 1. invoke parent close connection
	// 2. close self in 1.
	// 3. remove self in parent

	//tcp_connection_ptr guard_this(shared_from_this());
	//close_callback_(guard_this);
	close_callback_(shared_from_this());		// i think the invoker hold this shared_ptr, so don't need local holder
}

void tcp_connection::connect_destroyed(){
    try{
        if (is_open()){
            socket_.close();
            connection_callback_(shared_from_this());
        }
    }
    catch (const boost::exception& e){
        std::cerr << "socket close exception." << std::endl;
    }
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
    
    my::log lg;
    lg<<(data);
    
//    BOOST_LOG_TRIVIAL(trace) << data;
    
}
