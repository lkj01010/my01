////
//// server.cpp
//// ~~~~~~~~~~
////
//// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
////
//// Distributed under the Boost Software License, Version 1.0. (See accompanying
//// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////
//
//#include <array>
//#include <cstdlib>
//#include <iostream>
//#include <memory>
//#include <type_traits>
//#include <utility>
//#include <boost/asio.hpp>
//
//using boost::asio::ip::tcp;
//
//
//bool read = false; 
//void deadline_handler(const boost::system::error_code &) 
//{ std::cout << (read ? "read successfully" : "read failed") << std::endl;
//system("pause");
//} 
//
//void read_handler(const boost::system::error_code &) { read = true; } 
//
//
//
//
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
