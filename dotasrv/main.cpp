#include <cstring>
#include <climits>
#include "net/tcp_server.h"
#include "net/proto/http_codec.h"
#include "tencent_api.h"

 #include <boost/regex.hpp>

using boost::asio::ip::tcp;

using namespace net;
using namespace std;


void parse_request_param(std::map<std::string, std::string>& map, const std::string& request){
	std::string key = "";
	std::string cache = "";
	map.clear();
	for (int i = 0; i < request.size(); ++i)
	{
		const char& c = request[i];
		char word[2] = { c, '\0' };
		std::string cstr = word;
		if (c == '=')
		{
			key = cache;
			cache.clear();
		}
		else if (c == '&'){
			map.insert(std::pair<std::string,std::string>(key, cache));
			cache.clear();
		}
		else if (c == '?'){
			map.insert(std::pair<std::string,std::string>(key, cache));
			cache.clear();
		}
		else if (c == '/'){}	//skip
		else{
			cache.append(cstr);
		}
	}
}



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
                
			//////////////////////////////////////////////////////////////////////////

				//boost::regex expression(
				//	"/openid=(\\w+)"
				//	"&openkey=(\\w+)"
				//	"&pf=[\\w_]+"
				//	"&pfkey=\\w*"
				//	"&platform=([\\w_]+)"
				//	"&api=([\\w_]+)"
				//	"[?]callback=([\\w_]+)"
				//	"&_=\\d+"
				//	);

				//bool ismc = boost::regex_match(content, expression);
				//if (ismc)
				//{
				//	std::string::const_iterator start, end;
				//	start = content.begin();
				//	end = content.end();

				//	boost::match_results<std::string::const_iterator> what;
				//	boost::match_flag_type flags = boost::match_default;

				//	//int i = 0;
				//	if (regex_search(start, end, what, expression, flags))
				//	{
				//		//for (size_t i = 0; i < what.size(); ++i)
				//		//{
				//		//	if (what[i].matched)
				//		//		std::cout << string(what[i].first, what[i].second) << std::endl;
				//		//}

				//		SLOG_INFO << "parse result: openid=" << what[1] << " openkey=" << what[2] << " platform=" << what[3] << " api="
				//			<< what[4] << " callback=" << what[5];
				//	}


				//	//tapi_.handle_request( what[1], what[2], what[3], what[4]);
				//////////////////////////////////////////////////////////////////////////

				std::map<std::string, std::string> param_map;
				parse_request_param(param_map, content);
				std::string openid, openkey, platform, api;
				bool is_valid = true;
				std::map<std::string,std::string>::iterator it = param_map.find("openid");
				if (it != param_map.end())
				{
					openid = it->second;
				}
				else{
					is_valid = false;
				}
				it = param_map.find("openkey");
				if (it != param_map.end())
				{
					openkey = it->second;
				}
				else{
					is_valid = false;
				}
				it = param_map.find("platform");
				if (it != param_map.end())
				{
					platform = it->second;
				}
				else{
					is_valid = false;
				}
				it = param_map.find("api");
				if (it != param_map.end())
				{
					api = it->second;
				}
				else{
					is_valid = false;
				}
					 
				if (is_valid)
				{
					tapi_.handle_request(openid, openkey, platform, api);
				}
				else{
					SLOG_INFO << "client pass a invalid url.";
				}


				//////////////////////////////////////////////////////////////////////////
				//conn->send(http_codec::make_reply("indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need read any more, close connection indicate not need  "));
				//bool is_valid = false;
				////string content = "/fefex?callback=jxilcvjjvlj1212&_=192120129320";
				//string funcname;
				//long idx_1 = content.find("/");
				//long idx_2 = content.find("?");
				//long idx_3 = content.find_first_of("=");
				//long idx_4 = content.find("&");
				//if (idx_1 >= 0 && idx_2 > idx_1 && idx_3 > idx_2 && idx_4 > idx_3){
				//	funcname = content.substr(idx_3 + 1, idx_4 - idx_3 - 1);
				//	is_valid = true;
				//}

				//if (is_valid){
				//	conn->send(http_codec::make_reply(funcname + string("({ \"xx\":\"10\"})")));
				//	SLOG_DEBUG << "send:" << funcname + string("({ \"xx\":\"10\"})");
				//}
				//else{
				//	int i;
				//	SLOG_DEBUG << "parse url error. ";
				//}
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




//////////////////////////////////////////////////////////////////////////
// test Regex:
