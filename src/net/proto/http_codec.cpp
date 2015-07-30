#include "net/proto/http_codec.h"


using namespace net;
using namespace std;
using namespace http;

bool http_codec::decode(std::string& data){

	request req;
    boost::tribool result;
    std::string::iterator next_begin_it;    // if short connection, discard it;
    request_parser_.reset();				// reset the parser, it's a state machine
    boost::tie(result, next_begin_it) = request_parser_.parse(
		req, data.begin(), data.end());
    
    if (result) {
		data.assign(next_begin_it, data.end());
		return http_codec_callback_(req.uri);
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

string http_codec::make_reply(const std::string& content){
	reply rep;
	rep.status = reply::ok;
	rep.content = content;

	rep.headers.resize(3);
	
	rep.headers[0].name = "Content-Length";
	rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
	rep.headers[1].name = "Content-Type";
	rep.headers[1].value = "text/html";
	//lkj note: do steps below to allow ajax XMLHttpRequest GET access server
	// 1. download jquery-1.7.2.min.js
	// 2. client index.html add JSONP script:
	
	/*<script type = "text/javascript" src = "jquery-1.7.2.min.js">< / script>
		<script type = "text/javascript">
		jQuery(document).ready(function(){
			$.ajax({
			type: "get",
			  url : "http:127.0.0.1:12303",
				dataType : "jsonp",
					   jsonp : "callback",
						   jsonpCallback : "jsonpCallback",
									   success : function(json){
				alert('json:' + json);
									   },
									   error : function(){
				  alert('fail');
									   }
			});
		});
	< / script>*/
	
	// 3. add header "Access-Control-Allow-Origin" to relay
	rep.headers[2].name = "Access-Control-Allow-Origin";
	rep.headers[2].value = "*";
    string ret = rep.to_string();
    return ret;
}

string http_codec::make_bad_reply(){
	return reply::stock_reply(reply::bad_request).to_string();
}
