#include "net/tcp_server.h"
#include "net/proto/http_codec.h"
#include "tencent_api.h"

using boost::asio::ip::tcp;

using namespace net;
using namespace std;

typedef boost::weak_ptr<tcp_connection> weak_tcp_connection_ptr;
class pay_session{
public:
	explicit pay_session(const weak_tcp_connection_ptr& conn)
		: conn_(conn)
	{}
	bool handle_message(const string& content){
		SLOG_DEBUG << "pay_session message_callback:" << content;
        
		tcp_connection_ptr conn = conn_.lock();
		if (conn)
		{
            if(content.empty()){
                conn->send(http_codec::make_bad_reply());
            }else{
                
                tapi_.handle_request(content);
                
               conn->send(http_codec::make_reply("indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need  "));
            }
			
		}
		return false;	//indicate not need read any more, close connection
	}
    
	weak_tcp_connection_ptr conn_;
	//string str_;
    tencent_api tapi_;
    
};

class pay_server{
public:
	pay_server(const std::string& address, const std::string& port,
		std::size_t io_service_pool_size)
		: server_(address, port, io_service_pool_size)
		, n_conn_(0)
	{
		server_.set_connection_callback(boost::bind(&pay_server::connection_callback, this, _1));
		server_.set_message_callback(boost::bind(&pay_server::message_callback, this, _1, _2));

	}

	void connection_callback(const tcp_connection_ptr& connection_ptr){
		if (connection_ptr->is_open()){
			connection_ptr->set_module((void*)(new pay_session(boost::weak_ptr<tcp_connection>(connection_ptr))));
			n_conn_++;
		}
		else{
			pay_session *s = (pay_session*)connection_ptr->module();
			delete s;
			connection_ptr->set_module(nullptr);
			n_conn_--;
		}
		SLOG_DEBUG << "connection_callback , conn count = " << n_conn_;
	}

	bool message_callback(const tcp_connection_ptr& connection_ptr, std::string & data){
		pay_session *s = (pay_session*)connection_ptr->module();
		if (s){
			codec_.set_http_codec_callback(boost::bind(&pay_session::handle_message, s, _1));
			return codec_.decode(data);
		}
		else{
			return false;
		}
	}

	void run(){
		server_.run();
	}


	net::tcp_server server_;
	net::http_codec codec_;
	int n_conn_;
};


int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: http_server <threads>\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    receiver 0.0.0.0 80 1 .\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    receiver 0::0 80 1 .\n";
			return 1;
		}
#if defined _WIN32
        SLog::InitLog("./logs/dotalog");
#elif   defined _MAC
        SLog::InitLog("/Users/Midstream/Documents/Dev/git-me/my01/dotalog");
#else   //linux
       SLog::InitLog("./logs/dotalog");
#endif

		SLog::SetLevel(slog_debug);

		std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[1]);
		pay_server s("0.0.0.0", "12303", num_threads);   
		s.run();
	}
	catch (std::exception& e)
	{
		SLOG_EMERGENCY << "exception: " << e.what();
		system("pause");
	}

	return 0;
}
