#pragma once


//#include "message.h"
#include "com/common.h"
#include "net/proto/http/request.hpp"
#include "net/proto/http/reply.hpp"
#include "net/proto/http/request_handler.hpp"
#include "net/proto/http/request_parser.hpp"

namespace net
{

typedef boost::function<bool(const std::string&)> http_codec_callback;
class http_codec
{
public:
	http_codec()
    {}

    void set_http_codec_callback(const http_codec_callback& cb){
        http_codec_callback_ = cb;
    }
    
    bool decode(std::string& data); // return false indicates got a wrong request
	
//	static std::vector<boost::asio::const_buffer> make_replay(const std::string& content);
    static std::string make_reply(const std::string& content);
    static std::string make_bad_reply();
private:
	void handle_request();
private:
    http_codec_callback http_codec_callback_;
    
    //http::request request_;
	//http::reply reply_;
    http::request_handler request_handler_;
    http::request_parser request_parser_;
};

}