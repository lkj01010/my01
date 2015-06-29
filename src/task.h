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


class tasks_processor : private boost::noncopyable{
	boost::asio::io_service	ios_;
	boost::asio::io_service::work	work_;
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







