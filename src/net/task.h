#pragma once

#include "common.h"

#include <boost/asio/io_service.hpp>

#include <iostream>

#include "tcp_connection.h"

namespace detail{
    
    template<class T>
    struct task_wrapped{
    private:
        T task_unwrapped_;
    public:
        explicit task_wrapped(const T& task_unwrapped)
        : task_unwrapped_(task_unwrapped)
        {}
        
        void operator()() const {
            try{
                boost::this_thread::interruption_point();
            }
            catch (const boost::thread_interrupted&){}
            
            try{
                task_unwrapped_();
            }
            catch (const std::exception& e){
                std::cerr << "Exception: " << e.what() << '\n'; }
            catch (const boost::thread_interrupted&){
                std::cerr << "Thread interrupted\n"; }
            catch (...){
                std::cerr << "Unknown exception\n"; }
        }
    };
    
    template<class T>
    task_wrapped<T> make_task_wrapped(const T& task_unwrapped){
        return task_wrapped<T>(task_unwrapped);
    }
    
    
	//----------------------------------------------------------------------

    typedef boost::asio::deadline_timer::duration_type duration_type;
    
    template<class Functor>
    struct timer_task : public task_wrapped<Functor>{
    private:
        typedef task_wrapped<Functor> base_t;
        boost::shared_ptr<boost::asio::deadline_timer> timer_;
        
    public:
        template<class Time>
        explicit timer_task(
                            boost::asio::io_service& ios,
                            const Time& duration_or_time,
                            const Functor& task_unwrapped)
        : base_t(task_unwrapped)
        , timer_(boost::make_shared<boost::asio::deadline_timer>(
                                                                 boost::ref(ios), duration_or_time))
        {}
        
        void push_task() const {
            timer_->async_wait(*this);
        }
        
        void operator()(const boost::system::error_code& error) const{
            if (!error){
                base_t::operator()();
            }
            else{
                std::cerr << error << "\n";
            }
        }
    };
    
    template<class Time, class Functor>
    inline timer_task<Functor> make_timer_task(
                                               boost::asio::io_service& ios,
                                               const Time& duration_or_time,
                                               const Functor& task_unwrapped)
    {
        return timer_task<Functor>(ios, duration_or_time, task_unwrapped);
    }
    
}


//----------------------------------------------------------------------

class tasks_processor : public my::singleton<tasks_processor>
{
    boost::asio::io_service	ios_;
    boost::asio::io_service::work	work_;
protected:
    friend class my::singleton<tasks_processor>;
    tasks_processor()
    : ios_()
    , work_(ios_)
    {}
public:
    template<class T>
    inline void push_task(const T& task_unwrapped){
        ios_.post(detail::make_task_wrapped(task_unwrapped));
    }
    
    typedef boost::asio::deadline_timer::time_type time_type;
    template<class Functor>
    void run_at(time_type time, const Functor& f){
        detail::make_timer_task(ios_, time, f).push_task();
    }
    
    typedef boost::asio::deadline_timer::duration_type duration_type;
    template<class Functor>
    void run_after(duration_type duration, const Functor& f){
        detail::make_timer_task(ios_, duration, f).push_task();
    }
    
    tcp_connection_ptr create_connection(const char* addr,
                                         unsigned short port_num){
        return tcp_connection_ptr(ios_,
                                  boost::asio::ip::tcp::endpoint( boost::asio::ip::address_v4::from_string(addr),
                                                                 port_num)
                                  );
    }
    
    void start(){
        ios_.run();
    }
    
    void stop(){
        ios_.stop();
    }
    
};