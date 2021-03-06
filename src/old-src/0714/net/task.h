#pragma once

#include "common.h"

#include <boost/asio/io_service.hpp>

#include <iostream>

#include "tcp_connection.h"

using boost::asio::ip::tcp;
using namespace net;

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
    
    //----------------------------------------------------------------------
    
    class tcp_listener : public boost::enable_shared_from_this<tcp_listener>{
        typedef tcp::acceptor acceptor_t;
        acceptor_t acceptor_;
        
        boost::function<void(tcp_connection_ptr)> func_;
    public:
        template<class Functor>
        tcp_listener(
                     boost::asio::io_service& io_service,
                     unsigned short port,
                     const Functor& task_unwrapped)
        :acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
        ,func_(task_unwrapped)
        {}
        
        void push_task() {
            if(!acceptor_.is_open()){
                return;
            }
            
            typedef tcp::socket socket_t;
            boost::shared_ptr<socket_t> socket
            = boost::make_shared<socket_t>(boost::ref(acceptor_.get_io_service()));
            
            acceptor_.async_accept(*socket, 
            						boost::bind(
                                        &::detail::tcp_listener::handle_acceptor,
                                        this->shared_from_this(),
                                        tcp_connection_ptr(socket),
                                        boost::asio::placeholders::error));
        }
        
        void stop(){
            acceptor_.close();
        }
        
    private:
        void handle_acceptor(
                             const tcp_connection_ptr& new_connection,
                             const boost::system::error_code& error){
            push_task();
            
            if(!error){
                make_task_wrapped(boost::bind(func_, new_connection))();    //run it
            }else{
                std::cerr << error << '\n';
            }
        }
    };
    
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
                                  tcp::endpoint( boost::asio::ip::address_v4::from_string(addr),
                                                                 port_num)
                                  );
    }
    
    void start(){
        ios_.run();
    }
    
    void stop(){
        ios_.stop();
    }
    
    
    //////////////////////////
    typedef std::map<unsigned short, boost::shared_ptr<::detail::tcp_listener>> listeners_map_t;
    
    listeners_map_t listeners_;
    
    template<class Functor>
    void add_listener(unsigned short port_num, const Functor& f){
        listeners_map_t::const_iterator it = listeners_.find(port_num);
        if(it != listeners_.end()){
            throw std::logic_error(
            "such listener for port '"  + boost::lexical_cast<std::string>(port_num) + "' already created");  // exist
            
        }
    
        listeners_[port_num] = boost::make_shared<detail::tcp_listener>(boost::ref(ios_), port_num, f);
        listeners_[port_num]->push_task();
    }
    
    void remove_listener(unsigned short port_num){
        listeners_map_t::const_iterator it = listeners_.find(port_num);
        if(it == listeners_.end()){
            throw std::logic_error(
                "No listener for port '" + boost::lexical_cast<std::string>(port_num)+ "' created");  //
        }
        
        (*it).second->stop();
        listeners_.erase(it);
    }
    
};


