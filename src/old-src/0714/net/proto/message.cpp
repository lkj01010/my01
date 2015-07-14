#include "message.h"

#include <iostream>


using namespace net;

namespace net
{
    
namespace detail {
    inline int32_t asInt32(const char* buf)
    {
        int32_t be32 = 0;
        ::memcpy(&be32, buf, sizeof(be32));
        return ntohl(be32);
    }
    
    const int kHeaderLen = sizeof(uint32_t);
}
}


std::string message::encode(){
    std::string result;
    result.resize(detail::kHeaderLen);
    
    int32_t info = htonl(info_);
    result.append(reinterpret_cast<char*>(&info), sizeof(info));
    
    int32_t type = htonl(type_);
    result.append(reinterpret_cast<char*>(&type), sizeof(type));
    
    result.append(data_);
    
#ifdef USE_CHECKSUM
    const char* begin = result.c_str() + kHeaderLen;
    int32_t checksum = adler32(1, reinterpret_cast<const Bytef*>(begin), result.size() - kHeaderLen);
#else
    int32_t checksum = 123456;
#endif
    
    int32_t be32 = htonl(checksum);
    result.append(reinterpret_cast<char*>(&be32), sizeof(be32));
    
    int32_t len = htonl(result.size());
    std::copy(reinterpret_cast<char*>(&len), reinterpret_cast<char*>(&len) + sizeof(len), result.begin());
    
    return result;
}

bool message::decode(const std::string& buf)
{
    int32_t len = static_cast<int32_t>(buf.size());
    
    if (len > sizeof(int32_t)) {
        
        int32_t msg_len = detail::asInt32(buf.c_str());
        
        if (msg_len <= len) {
            int32_t expected_checksum = detail::asInt32(buf.c_str() + buf.size() - detail::kHeaderLen);
#ifdef USE_CHECKSUM
            const char* begin = buf.c_str();
            int32_t checksum = adler32(1, reinterpret_cast<const Bytef*>(begin), len - detail::kHeaderLen);
#else
            int32_t checksum = 123456;
#endif
            if (checksum == expected_checksum)
            {
                int32_t info = detail::asInt32(buf.c_str() + detail::kHeaderLen);
                set_info(info);
                int32_t type = detail::asInt32(buf.c_str() + 2*detail::kHeaderLen);
                set_type(type);
                
                const char* data = buf.c_str() + 3*detail::kHeaderLen;
                int32_t data_len = len - 4*detail::kHeaderLen;
                data_.append(data, data_len);
            }
            else
            {
                throw std::logic_error("message checksum error");
                return false;
            }
        }
        else{
            return false;   //size not enough
        }
    }else{
        return false;
    }

    return true;
};
