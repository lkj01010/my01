#include "tcp_server.h"
#include "message.h"

using boost::asio::ip::tcp;
using namespace net;
using namespace std;

class session{
public:

	string str_;
};

class echo_server{

	echo_server(const std::string& address, const std::string& port,
	std::size_t io_service_pool_size)
	: server_(address, port, 2)
	{
		server_.set_connection_callback(boost::bind(&echo_server::connection_callback, this, _1));
		server_.set_message_callback(boost::bind(&echo_server::message_callback, this, _1));
	}

	void message_callback(const net::message& msg, const tcp_connection_ptr& connection_ptr){
		std::string content = msg.get_content();
		
		boost::shared_ptr<void> obj = connection_ptr->tie();
		void *v = obj.get();
		session *s = dynamic_cast<session*>(v);
		s->str_;
	}

	void connection_callback(const tcp_connection_ptr& connection_ptr){
		connection_ptr->tie(boost::make_shared<session>(new session));
	}


	net::tcp_server server_;
};
