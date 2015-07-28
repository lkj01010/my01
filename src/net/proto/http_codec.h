#pragma once


//#include "message.h"
#include "common.h"
#include "request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"

namespace net
{

typedef boost::function<bool(std::string&)> http_codec_callback;
class http_codec
{
public:
	http_codec()
    {}

    void set_http_codec_callback(const http_codec_callback& cb){
        http_codec_callback_ = cb;
    }
    
    bool decode(std::string& data); // return false indicates got a wrong request

private:
    http_codec_callback http_codec_callback_;
    
    http::request request_;
    http::request_handler request_handler_;
    http::request_parser request_parser_;
};

}