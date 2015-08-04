#include <cstring>
#include <climits>
#include "net/tcp_server.h"
#include "net/proto/http_codec.h"
#include "tencent_api.h"

#include "com/log.h"
// #include <boost/regex.hpp>

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
                
               //conn->send(http_codec::make_reply("indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need  "));

				/*long idx = content.find_last_of("=");
				string funcname = content.substr(idx + 1, funcname.size() - idx);*/
				//SLOG_DEBUG << "funcname:" << funcname;
				//conn->send(http_codec::make_reply(funcname + string("({ \"xx\":\"10\"})")));
				
				bool is_valid = false;
				//string content = "/fefex?callback=jxilcvjjvlj1212&_=192120129320";
				string funcname;
				long idx_1 = content.find("/");
				long idx_2 = content.find("?");
				long idx_3 = content.find_first_of("=");
				long idx_4 = content.find("&");
				if (idx_1 >= 0 && idx_2 > idx_1 && idx_3 > idx_2 && idx_4 > idx_3){
					funcname = content.substr(idx_3 + 1, idx_4 - idx_3 - 1);
					is_valid = true;
				}

				if (is_valid){
					conn->send(http_codec::make_reply(funcname + string("({ \"xx\":\"10\"})")));
					SLOG_DEBUG << "send:" << funcname + string("({ \"xx\":\"10\"})");
				}

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
			connection_ptr->set_module(NULL);
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
	string content = "/fefex?callback=jxilcvjjvlj1212&_=192120129320";
	string funcname;
	long idx_1 = content.find("/");
	long idx_2 = content.find("?");
	long idx_3 = content.find_first_of("=");
	long idx_4 = content.find("&");
	if (idx_1 >= 0 && idx_2 > idx_1 && idx_3 > idx_2 && idx_4 > idx_3){
		funcname = content.substr(idx_3+1, idx_4 - idx_3 -1);
	}


	//
	////?、*、<、>、=、/、1这些都不需要转义的。无需加 \

	////boost::regex e1("[0-9]+");
	///*boost::regex expression(
	//	"^(/?callback=/)"
	//	"(\\w+)"
	//	"(/&_/\\d+)"
	//	);*/

	//boost::regex expression(
	//	"^(\\</?callback=\\>)"
	//	"\\<\\w+\\>"
	//	"(\\<\&_=\>(\\d+)"

	//	);

	//std::string::const_iterator start, end;
	//start = str.begin();
	//end = str.end();

	//boost::match_results<std::string::const_iterator> what;
	//boost::match_flag_type flags = boost::match_default;

	//while (regex_search(start, end, what, expression, flags))
	//{
	//	SLOG_DEBUG << "regex: " << string(what[0].first, what[0].second);
	//	start = what[0].second;
	//}

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
