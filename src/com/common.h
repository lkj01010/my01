#pragma once


#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>



#include <boost/system/error_code.hpp>


#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>


#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>



#include <boost/thread/thread.hpp>

#include <boost/lexical_cast.hpp>



#if defined(_WIN32)
#include <winsock2.h>
#include <windows.h>
#endif



#include "singleton.h"
