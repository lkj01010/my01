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

using boost::asio::ip::tcp;

namespace net
{

	class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
	{

	public:
		tcp_connection(boost::asio::io_service& io_service)
			: socket_(io_service)
		{
		}

		tcp::socket& socket(){ return socket_; }

	private:
		tcp::socket socket_;
	};

	typedef boost::shared_ptr<tcp_connection> tcp_connection_ptr;









	//class tcp_connection_ptr{
	//    boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
	//    
	//public:
	//    explicit tcp_connection_ptr(
	//        boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
	//    : socket_(socket)
	//    {}
	//    
	//    explicit tcp_connection_ptr(
	//                                boost::asio::io_service& ios,
	//                                const boost::asio::ip::tcp::endpoint& endpoint)
	//    : socket_(boost::make_shared<boost::asio::ip::tcp::socket>(boost::ref(ios)))
	//    {
	//        socket_->connect(endpoint);
	//    }
	//    
	//    template<class Functor>
	//    void async_read(
	//                    const boost::asio::mutable_buffers_1& buf,
	//                    const Functor& f,
	//                    std::size_t at_least_bytes) const
	//    {
	//        boost::asio::async_read(*socket_, buf, boost::asio::transfer_at_least(at_least_bytes), f);
	//    }
	//    
	//    template<class Functor>
	//    void async_write(
	//                     const boost::asio::const_buffers_1& buf,
	//                     const Functor& f) const
	//    {
	//        boost::asio::async_write(*socket_, buf, f);
	//    }
	//    
	//    template<class Functor>
	//    void async_write(
	//                     const boost::asio::mutable_buffers_1& buf,
	//                     const Functor& f) const
	//    {
	//        boost::asio::async_read(*socket_, buf, f);
	//    }
	//    
	//    void shutdown() const {
	//        socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	//        socket_->close();
	//    }
	//    
	//    
	//};

}

#endif /* defined(__my01__tcp_connection__) */
