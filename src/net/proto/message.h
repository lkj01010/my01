#pragma once
#include "common.h"
class message
{
public:
	message()
	{}

	~message()
	{}

	inline void set_info(int32_t info){ info_ = info; }
	inline int32_t info()const{ return info_; }

	inline void set_type(int32_t type){ type_ = type; }
	inline int32_t type()const{ return type_; }

	inline void set_data(const std::string& data){ data_ = data; }
	inline std::string data()const { return data_; }
	
	inline void append_to_string(std::string& str)const{
		str.append(data_);
	}

	inline void parse_from_array(const char* data, int32_t len){
		data_.append(data, len);
	}
private:
	int32_t info_;
	int32_t type_;
	std::string data_;

};

