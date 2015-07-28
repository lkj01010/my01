#include "msg_codec.h"

using namespace net;
using namespace std;

bool msg_codec::decode(std::string& data){
    message msg;
    while (!data.empty()){
        int lenght = msg.parse_from_string(data);
        if (lenght > 0)
        {
            data = data.substr(lenght);
  
            if(msg_codec_callback_(msg)){
            }
            else{
                return false;   // wrong msg, close connection
            }
        }
        else if (lenght == 0){  //require more data
            return true;
        }
        else{
            SLOG_WARNING << "message_callback parsed data len < 0";
            return false;   // wrong msg, close connection
        }
    }
    return true;
}

