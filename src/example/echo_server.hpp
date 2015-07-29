#include "net/tcp_server.h"
#include "net/proto/msg_codec.h"

#include "boost/date_time/posix_time/time_formatters.hpp"

using boost::asio::ip::tcp;
using namespace net;
using namespace std;


typedef boost::weak_ptr<tcp_connection> weak_tcp_connection_ptr;

class echo_session{
public:
	explicit echo_session(const weak_tcp_connection_ptr& conn)
		: conn_(conn)
	{}
	bool handle_message(const net::message& data){
		std::string content = data.get_content();

		SLOG_DEBUG << "message_callback:" << content;
		
		tcp_connection_ptr conn = conn_.lock();
		if (conn)
		{
			//conn->send(boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()));
			conn->send(content);
		}
        return true;
	}
    

	// if you don't want to send msg to sever , conn holder is not necessary
	weak_tcp_connection_ptr conn_;
	string str_;
};

class echo_server{
public:
	echo_server(const std::string& address, const std::string& port,
		std::size_t io_service_pool_size)
		: server_(address, port, io_service_pool_size)
//        , codec_()
		, n_conn_(0)
	{
		server_.set_connection_callback(boost::bind(&echo_server::connection_callback, this, _1));
		server_.set_message_callback(boost::bind(&echo_server::message_callback, this, _1, _2));
        
	}

	void connection_callback(const tcp_connection_ptr& connection_ptr){
		if (connection_ptr->is_open()){
			connection_ptr->set_module((void*)(new echo_session(boost::weak_ptr<tcp_connection>(connection_ptr))));
			n_conn_++;
		}
		else{
			n_conn_--;
		}
		SLOG_DEBUG << "new connection. n_conn = " << n_conn_;
	}

	bool message_callback(const tcp_connection_ptr& connection_ptr, std::string & data){
//		net::message message;
//		while (!data.empty()){
//			int lenght = message.parse_from_string(data);
//			if (lenght > 0)
//			{
//				data = data.substr(lenght);
//
//				echo_session *s = (echo_session*)connection_ptr->module();
//				s->handle_message(message);
//			}
//			else if (lenght == 0){}
//			else{
//				SLOG_ERROR << "message_callback parsed data len < 0";
//				break;
//			}
//		}
        echo_session *s = (echo_session*)connection_ptr->module();
        if(s){
            codec_.set_msg_codec_callback(boost::bind(&echo_session::handle_message, s, _1));
            return codec_.decode(data);
        }else{
            return false;
        }
        
	}

	

	void run(){
		server_.run();
	}


	net::tcp_server server_;
    net::msg_codec codec_;
	int n_conn_;
}; 