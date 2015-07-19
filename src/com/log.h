//
//  log.h
//  my01
//
//  Created by 林 科俊 on 15/7/20.
//  Copyright (c) 2015年 mid. All rights reserved.
//

#ifndef __my01__log__
#define __my01__log__

#define BOOST_LOG_DYN_LINK 1

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <iostream>

#include <fstream>


#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include <boost/log/sources/logger.hpp>

#include <boost/log/support/date_time.hpp>


namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;


namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;


enum severity_level
{
    normal,
    notification,
    warning,
    error,
    critical
};

// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
    static const char* const str[] =
    {
        "normal",
        "notification",
        "warning",
        "error",
        "critical"
    };
    if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast< int >(lvl);
    return strm;
}

namespace my
{
    
class log{
public:
    log(){
        logging::add_console_log(std::clog, keywords::format = "%TimeStamp%: %Message%");
        
        namespace fs=boost::filesystem;
//        std::string dir = "\\Users\\Midstream\\Documents\\Dev\\git-me\\my01\\sample.log";
//        bf::path file_path( "Users\Midstream\Documents\Dev\git-me\my01\");
        std::string file_path = "/Users/Midstream/Documents/Dev/git-me/my01/sssss.log";
        std::ofstream ff( file_path.c_str(), std::ios_base::out | std::ios_base::binary );      // or   fs::ofstream    all ok!!!!!!!
//        file_path /= "sample.log";
//        if (boost::filesystem::exists(file_path) == false)
//        {
////            boost::filesystem::create_directory(dir);
//            std::ofstream f;
//            f.open(file_path.c_str());
//        }
        logging::add_file_log
        (
         file_path,
         keywords::filter = expr::attr< severity_level >("Severity") >= normal,
         keywords::format = expr::stream
         << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d, %H:%M:%S.%f")
         << " [" << expr::format_date_time< attrs::timer::value_type >("Uptime", "%O:%M:%S")
         << "] [" << expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)")
         << "] <" << expr::attr< severity_level >("Severity")
         << "> " << expr::message
        /*
         keywords::format = expr::format("%1% [%2%] [%3%] <%4%> %5%")
         % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d, %H:%M:%S.%f")
         % expr::format_date_time< attrs::timer::value_type >("Uptime", "%O:%M:%S")
         % expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)")
         % expr::attr< severity_level >("Severity")
         % expr::message
         */
         );
        
        // Also let's add some commonly used attributes, like timestamp and record counter.
        logging::add_common_attributes();
        logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());
    }
    
    void logger(){
        
        
    }
    
    void operator<<(std::string what){
        BOOST_LOG_FUNCTION();
        
        src::logger lg;
        
        // And output...
        
        BOOST_LOG(lg) << what + "fjeijfei" << "  append!!!!  ";
        
        src::severity_logger< severity_level > slg;
        
        // Let's pretend we also want to profile our code, so add a special timer attribute.
        slg.add_attribute("Uptime", attrs::timer());
        
        BOOST_LOG_SEV(slg, normal) << "A normal severity message, will not pass to the file";
        BOOST_LOG_SEV(slg, warning) << "A warning severity message, will pass to the file";
        BOOST_LOG_SEV(slg, error) << "An error severity message, will pass to the file";
    }
    
//    src::logger lg_;
};

}


//#include <boost/log/trivial.hpp>
//#include <boost/log/core.hpp>
//#include <boost/log/expressions.hpp>



#endif /* defined(__my01__log__) */
