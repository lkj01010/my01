#include "tcp_server.h"
#include "message.h"

#include "boost/date_time/posix_time/time_formatters.hpp"

using boost::asio::ip::tcp;
using namespace net;
using namespace std;

class session{
public:

	string str_;
};

class echo_server{
public:
	echo_server(const std::string& address, const std::string& port,
	std::size_t io_service_pool_size)
	: server_(address, port, io_service_pool_size)
	{
		server_.set_connection_callback(boost::bind(&echo_server::connection_callback, this, _1));
		server_.set_message_callback(boost::bind(&echo_server::message_callback, this, _1, _2, _3));
	}

	void connection_callback(const tcp_connection_ptr& connection_ptr){
		connection_ptr->set_module((void*)(new session()));
	}

	void message_callback(const tcp_connection_ptr& connection_ptr, const net::message& msg, boost::posix_time::ptime time){
		std::string content = msg.get_content();
		content = content +boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) + "\n";
		
		session *s = (session*)connection_ptr->module();

		s->str_ = boost::posix_time::to_simple_string(time);
		
		connection_ptr->send(content);
	}

	void run(){
		server_.run();
	}


	net::tcp_server server_;
}; 