//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "common.h"

using boost::asio::ip::tcp;


bool read = false; 
void deadline_handler(const boost::system::error_code &) 
{ std::cout << (read ? "read successfully" : "read failed") << std::endl;
system("pause");
} 

void read_handler(const boost::system::error_code &) { read = true; } 




//int main(int argc, char* argv[])
//{
//  try
//  {
//	  boost::asio::io_service io_service;
//	  tcp::socket sock(io_service);
//	  read = false;
//	  char data[512];
//	  sock.async_read_some(boost::asio::buffer(data, 512),
//		  [](boost::system::error_code ec, std::size_t length)
//			{
//				read = true;
//			}
//		  );
//		
//	  boost::asio::deadline_timer t(io_service, boost::posix_time::milliseconds(4000));
//
//	  t.async_wait(&deadline_handler);
//
//	  io_service.run();
//  }
//  catch (std::exception& e)
//  {
//    std::cerr << "Exception: " << e.what() << "\n";
//  }
//
//  return 0;
//}

#include "task.h"
#include "mongo_test.h"

int g_val = 0;
void func_test(){
	++g_val;
	if (g_val == 3){
		throw std::logic_error("Just checking");
	}

	boost::this_thread::interruption_point();
	if (g_val == 10) {
		throw boost::thread_interrupted();
	}
	if (g_val == 90){
		//tasks_processor::get().stop();
	}
}

int main(){
	boost::shared_ptr<DBClientBase> conn = mongoc::mongo_init();
	if (conn == NULL)
	{
		return -1;
	}
	static const std::size_t tasks_count = 10000;
	BOOST_STATIC_ASSERT(tasks_count >= 90);
	for (std::size_t i = 0; i < tasks_count; ++i)
	{
		tasks_processor::get().push_task(&func_test);
		tasks_processor::get().push_task(
			boost::bind(std::plus<int>(), 2, 2) );
		tasks_processor::get().push_task(boost::bind(&mongoc::insert, conn.get(), "eliot", i));

	}

	assert(g_val == 0);

	tasks_processor::get().start();
	//assert(g_val == 90);

	return 0;
}