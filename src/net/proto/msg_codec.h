#pragma once


#include "message.h"
#include "common.h"

namespace net
{

typedef boost::function<bool(message&)> msg_codec_callback;
class msg_codec
{
public:
	msg_codec()
    {}

    void set_msg_codec_callback(const msg_codec_callback& cb){
        msg_codec_callback_ = cb;
    }
    
    bool decode(std::string& data);

private:
    msg_codec_callback msg_codec_callback_;
};

}