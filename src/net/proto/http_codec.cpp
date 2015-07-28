#include "http_codec.h"


using namespace net;
using namespace std;

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
        return false;
    }
    else{   // more data is required
        return true;
    }
    
}

