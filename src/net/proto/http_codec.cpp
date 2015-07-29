#include "net/proto/http_codec.h"


using namespace net;
using namespace std;
using namespace http;

bool http_codec::decode(std::string& data){

    boost::tribool result;
    std::string::iterator next_begin_it;    // if short connection, discard it;
    boost::tie(result, next_begin_it) = request_parser_.parse(
              request_, data.begin(), data.end());
    
    if (result) {
        return http_codec_callback_(request_.uri);
    }
    else if(!result){
        SLOG_WARNING << "http_codec get a bad_request";
		//const string& reply_data = reply::stock_reply(reply::bad_request).to_buffers();
		http_codec_callback_("");
        return false;
    }
    else{   // more data is required
        return true;
    }
    
}

const string http_codec::make_replay(const std::string& content){
	reply rep;
	rep.status = reply::ok;
	rep.content = content;

	rep.headers.resize(2);
	rep.headers[0].name = "Content-Length";
	rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
	rep.headers[1].name = "Content-Type";
	rep.headers[1].value = "text/plain;charset=UTF-8";
}

const string http_codec::make_bad_replay(){
	return reply::stock_reply(reply::bad_request).to_buffers();
}
