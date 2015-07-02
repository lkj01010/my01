#pragma once

#include "common.h"

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

}




template<typename T>
class singleton : boost::noncopyable
{
public:
    static T& instance()
    {
        pthread_once(&ponce_, &singleton::init);
        return *value_;
    }
    
private:
    singleton();
    ~singleton();
    
    static void init()
    {
        value_ = new T();
    }
    
    static void destroy()
    {
        typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
        T_must_be_complete_type dummy; (void) dummy;
        
        delete value_;
    }
    
private:
    static pthread_once_t ponce_;
    static T*             value_;
};

template<typename T>
pthread_once_t singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* singleton<T>::value_ = NULL;







class tasks_processor
: private boost::noncopyable
{
	boost::asio::io_service	ios_;
	boost::asio::io_service::work	work_;
public:
	tasks_processor()
		: ios_()
		, work_(ios_)
	{}
public:
 
	static tasks_processor& get(){
		return s_inst_;
	}

	template<class T>
	inline void push_task(const T& task_unwrapped){
		ios_.post(detail::make_task_wrapped(task_unwrapped));
	}

	void start(){
		ios_.run();
	}

	void stop(){
		ios_.stop();
	}

private:
	static tasks_processor s_inst_;
};







