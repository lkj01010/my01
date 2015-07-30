//
//  tcp_connection.cpp
//  my01
//
//  Created by 林 科俊 on 15/7/4.
//  Copyright (c) 2015年 mid. All rights reserved.
//

#include "net/tcp_connection.h"
#include "net/proto/message.h"

using namespace net;

using boost::asio::ip::tcp;
using namespace std;

void net::default_connection_callback(const tcp_connection_ptr& conn)
{
	// do not call conn->forceClose(), because some users want to register message callback only.
	SLOG_DEBUG << "default_connection_callback";
}

bool net::default_message_callback(const tcp_connection_ptr&, std::string&)
{
	SLOG_DEBUG << "default_message_callback";
    return true;
}

//----------------------------------------------------------------------

tcp_connection::tcp_connection(boost::asio::io_service& io_service)
	: ios_(io_service)
	, socket_(io_service)
	, strand_(io_service)
    , module_(nullptr)
{}

tcp_connection::~tcp_connection(){
    if (module_) {
        SLOG_ERROR << "module must dealloc out of connection !!!";
    }
}

void tcp_connection::connect_established()
{
	connection_callback_(shared_from_this());

	socket_.async_read_some(boost::asio::buffer(rev_buffer_),
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
        if(bytes_transferred > 0){
            //         message msg;
            //msg.set_content(string(buffer_.data(), buffer_.data() + bytes_transferred));
            //         message_callback_(shared_from_this(), msg, boost::posix_time::second_clock::local_time());
            //
            //         bool result = false;
            
            rev_string_.append(rev_buffer_.data(), bytes_transferred);
            
            bool result = message_callback_(shared_from_this(), rev_string_);
            
            if (result)
            {
                socket_.async_read_some(boost::asio::buffer(rev_buffer_),
                                        //boost::asio::buffer(rev_buffer_, rev_buffer_size),			// or use this ?  need test
                                        boost::bind(&tcp_connection::handle_read, shared_from_this(),
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
            }
            else
            {
                close();
            }
        }else if(bytes_transferred == 0){
            close();        // client first close
        }

    }
    else{
        close();
		SLOG_WARNING << "tcp_connection closed. handle_read." << e.value() << e.message();
        
    }

	// If an error occurs then no new asynchronous operations are started. This
	// means that all shared_ptr references to the connection object will
	// disappear and the object will be destroyed automatically after this
	// handler returns. The connection class's destructor closes the socket.
}

void tcp_connection::handle_write(const boost::system::error_code& e, const size_t size)
{
    SLOG_DEBUG << "write size:" << size;
    
    send_queue_.pop_front();
    // there would be much accumulated commands before socket is closed. When this occurs, discard them.
    if (is_open()){
        if (!e)
        {
            if(send_queue_.empty() == false)
            {
                this->actual_write_data();
            }
        }
        else{
            close();
			SLOG_DEBUG << "tcp_connection closed in handle_write() with value[" << e.value()  << "] message[" << e.message() << "]";
        }
    }
}

//lkj todo: need default ?
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
			//FIXME: need ? how ?
            //// Initiate graceful connection closure.
            //boost::system::error_code ignored_ec;
            //socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
            
			socket_.close();
            connection_callback_(shared_from_this());
        }
    }
    catch (const boost::exception& e){
		SLOG_WARNING << "socket close exception: ";
    }
}

void tcp_connection::send(const string& data)
{
	if (!is_open()) {
		return;
	}
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
		SLOG_WARNING << "_strand.post: send_data, error:" << e.what();
	};
}

//void tcp_connection::send(const std::vector<boost::asio::const_buffer>& buffers){
//    if (!is_open()) {
//        return;
//    }
//    try {
//        strand_.dispatch( boost::bind( &tcp_connection::handle_send_array,
//                                      shared_from_this(), buffers));
//    }
//    catch (const boost::bad_weak_ptr& e) {
//        SLOG_WARNING << "_strand.post: send_data, error:" << e.what();
//    };
//}

void tcp_connection::handle_send(const std::string& data){
    send_queue_.push_back(data);
	if (send_queue_.size() > 1)
	{
		return;
	}
	else{
		actual_write_data();
	}
}

//void tcp_connection::handle_send_array(const std::vector<boost::asio::const_buffer>& buffers){
//    unsigned long old_size = send_queue_.size();
//    
//    for(int i = 0; i < buffers.size(); ++i){
//        send_queue_.push_back(buffers[i]);
//    }
//    
//    if (old_size > 0)
//    {
//        return;
//    }
//    else{
//        actual_write_data();
//    }
//}

void tcp_connection::actual_write_data(){
    const string& output = send_queue_[0];
    boost::asio::async_write(
                             socket_,
                             boost::asio::buffer(output), boost::asio::transfer_at_least(output.size()),
                             strand_.wrap(boost::bind(&tcp_connection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred))
                             );

}
