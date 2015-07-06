// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)
// modified by: lkj

#pragma once

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <zlib.h>  // adler32

#include <string>

#include <arpa/inet.h>  // htonl, ntohl
#include <stdint.h>

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
//   uint32_t  len;
//   int32_t   type;
//   char      data[len-6];
//   int32_t   checkSum;
// }

const int kHeaderLen = sizeof(uint32_t);

 //MSG should implement:1.type()  2.append_to_string(std::string)
template<class MSG>  
inline std::string encode(const MSG& message)
{
  std::string result;

  result.resize(kHeaderLen);

  const int_32& type = message.type();
  int32_t be32 = ::htonl(type);
  result.append(reinterpret_cast<char*>(&be32), sizeof be32);
  bool succeed = message.append_to_string(&result);

  if (succeed)
  {
    const char* begin = result.c_str() + kHeaderLen;
    int32_t checkSum = adler32(1, reinterpret_cast<const Bytef*>(begin), result.size()-kHeaderLen);
    int32_t be32 = ::htonl(checkSum);
    result.append(reinterpret_cast<char*>(&be32), sizeof be32);
    
    int32_t len = ::htonl(result.size() - kHeaderLen);
    std::copy(reinterpret_cast<char*>(&len),
              reinterpret_cast<char*>(&len) + sizeof len,
              result.begin());
  }
  else
  {
    result.clear();
  }

  return result;
}

inline int32_t asInt32(const char* buf)
{
  int32_t be32 = 0;
  ::memcpy(&be32, buf, sizeof(be32));
  return ::ntohl(be32);
}

///
/// Decode protobuf Message from transport format defined above.
/// returns a Message*
///
/// returns NULL if fails.
///
inline std::string decode(const std::string& buf)
{
  google::protobuf::Message* result = NULL;

  int32_t len = static_cast<int32_t>(buf.size());
  if (len >= 10)
  {
    int32_t expectedCheckSum = asInt32(buf.c_str() + buf.size() - kHeaderLen);
    const char* begin = buf.c_str();
    int32_t checkSum = adler32(1, reinterpret_cast<const Bytef*>(begin), len-kHeaderLen);
    if (checkSum == expectedCheckSum)
    {
      int32_t nameLen = asInt32(buf.c_str());
      if (nameLen >= 2 && nameLen <= len - 2*kHeaderLen)
      {
        std::string typeName(buf.begin() + kHeaderLen, buf.begin() + kHeaderLen + nameLen - 1);
        google::protobuf::Message* message = createMessage(typeName);
        if (message)
        {
          const char* data = buf.c_str() + kHeaderLen + nameLen;
          int32_t dataLen = len - nameLen - 2*kHeaderLen;
          if (message->ParseFromArray(data, dataLen))
          {
            result = message;
          }
          else
          {
            // parse error
            delete message;
          }
        }
        else
        {
          // unknown message type
        }
      }
      else
      {
        // invalid name len
      }
    }
    else
    {
      // check sum error
    }
  }

  return result;
}

