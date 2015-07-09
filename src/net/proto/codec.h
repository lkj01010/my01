// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)
// modified by: lkj

#pragma once

#include "common.h"

//#define USE_CHECKSUM
#ifdef USE_CHECKSUM
#include <zlib.h>  // adler32
#endif

//#include <arpa/inet.h>  // htonl, ntohl


// struct ProtobufTransportFormat __attribute__ ((__packed__))
// {
//   int32_t  len;
//   int32_t  nameLen;
//   char     typeName[nameLen]; 
//   char     protobufData[len-nameLen-8];
//   int32_t  checkSum; // adler32 of nameLen, typeName and protobufData
// }

// ------------------>lkj change to:
// {
//   int32_t  len;
//    int32_t   info;  // just like which server, userid etc.
//   int32_t   type;    // msg type
//   char      data[len-6];
//   int32_t   checkSum;
// }

const int kHeaderLen = sizeof(uint32_t);

//MSG should implement:
//0.info()    set_info(int32_t)
//1.type()    set_type(int32_t)
//2.append_to_string(std::string)
//3.parse_from_array(char*, uint32_t)

template<class MSG>  
inline std::string encode(const MSG& message)
{
	std::string result;

	result.resize(kHeaderLen);

	int32_t info = ::htonl(message.info());
	result.append(reinterpret_cast<char*>(&info), sizeof info);

	int32_t type = ::htonl(message.type());
	result.append(reinterpret_cast<char*>(&type), sizeof type);

	message.append_to_string(boost::ref(result));
    
#ifdef USE_CHECKSUM
	const char* begin = result.c_str() + kHeaderLen;
	int32_t checkSum = adler32(1, reinterpret_cast<const Bytef*>(begin), result.size() - kHeaderLen);
#else
	int32_t checkSum = 123456;
#endif
   
    int32_t be32 = ::htonl(checkSum);
    result.append(reinterpret_cast<char*>(&be32), sizeof be32);
    
    int32_t len = ::htonl(result.size() - kHeaderLen);
    std::copy(reinterpret_cast<char*>(&len),
              reinterpret_cast<char*>(&len) + sizeof len,
              result.begin());
	return result;
}

//inline int16_t asInt16(const char* buf){
//    int32_t be16 = 0;
//    ::memcpy(&be16, buf, sizeof(be16));
//    return ::ntohs(be16);
//}

inline int32_t asInt32(const char* buf)
{
	int32_t be32 = 0;
	::memcpy(&be32, buf, sizeof(be32));
	return ::ntohl(be32);
}

template<class MSG>
inline bool decode(const std::string& buf, MSG& message)
{
	bool ret = false;
	int32_t len = static_cast<int32_t>(buf.size());
	if (len >= 10)
	{
		int32_t expectedCheckSum = asInt32(buf.c_str() + buf.size() - kHeaderLen);
#ifdef USE_CHECKSUM
		const char* begin = buf.c_str();
		int32_t checkSum = adler32(1, reinterpret_cast<const Bytef*>(begin), len-kHeaderLen);
#else
		int32_t checkSum = 123456;
#endif
		if (checkSum == expectedCheckSum)
		{
			int32_t info = asInt32(buf.c_str() + kHeaderLen);
			message.set_info(info);
			int32_t type = asInt32(buf.c_str() + 2*kHeaderLen);
			message.set_type(type);
		
			const char* data = buf.c_str() + 3*kHeaderLen;
			int32_t data_len = len - 4*kHeaderLen;
			message.parse_from_array(data, data_len);

			ret = true;
		}
		else
		{
		  // check sum error
		}
	}

  return ret;
}

