#pragma once

//c
#include "stdlib.h"

//c++
#include <string>
#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <stdint.h>
#include <unordered_map>



#include <boost/system/error_code.hpp>


#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/thread.hpp>
#include <boost/lexical_cast.hpp>


#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>







#if defined(_WIN32)
#include <winsock2.h>
#include <windows.h>
#else
#include <arpa/inet.h>  // htonl, ntohl
#endif



#include "singleton.h"
