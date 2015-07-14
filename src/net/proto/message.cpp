#include "message.h"
#include <cstring>
#include <cassert>


static const uint16_t MSG_PAD = 0x1234;
static const uint32_t MAX_MSG_SIZE = 65535;

using namespace net;

message::message()
{
	this->pad_ = 0;
	this->size_ = 0;
	this->cmd_ = 0;
	this->encrypt_ = 0;
	this->param_ = 0;
};


message::message(uint16_t cmd, uint8_t encrypt, uint16_t param, const std::string& content)
: content_(content)
{
	this->pad_ = 0;
	this->size_ = 0;
	this->cmd_ = cmd;
	this->encrypt_ = encrypt;
	this->param_ = param;
}


std::string message::serialize_head_as_string() const
{
	std::string str;
	str.append((const char*)&this->pad_, sizeof(this->pad_));
	str.append((const char*)&this->size_, sizeof(this->size_));
	str.append((const char*)&this->cmd_, sizeof(this->cmd_));
	str.append((const char*)&this->encrypt_, sizeof(this->encrypt_));
	str.append((const char*)&this->param_, sizeof(this->param_));

	assert(str.size() == MSG_HEAD_SIZE);
	return str;
}

void message::serialize_head_to_string(std::string& str) const
{
	str = this->serialize_head_as_string();
}

int message::parse_head_from_string(const std::string& str)
{
	if (str.length() < MSG_HEAD_SIZE) {
		return 0;
	}

	const char* data = str.c_str();

	memcpy(&this->pad_, data, sizeof(this->pad_));
	data += sizeof(this->pad_);

	memcpy(&this->size_, data, sizeof(this->size_));
	data += sizeof(this->size_);

	memcpy(&this->cmd_, data, sizeof(this->cmd_));
	data += sizeof(this->cmd_);

	memcpy(&this->encrypt_, data, sizeof(this->encrypt_));
	data += sizeof(this->encrypt_);

	memcpy(&this->param_, data, sizeof(this->param_));
	data += sizeof(this->param_);

	return MSG_HEAD_SIZE;
}

std::string message::serialize_as_string() const
{
	this->pad_ = MSG_PAD;
	this->size_ = MSG_HEAD_SIZE + this->content_.size();
	return this->serialize_head_as_string() + this->content_;
}


void message::serialize_to_string(std::string& str) const
{
	str.clear();
	str = this->serialize_as_string();
}


int message::parse_from_string(const std::string& str)
{
	if (this->parse_head_from_string(str) == 0) {
		return 0;
	}

	if (this->pad_ != MSG_PAD || this->size_ < MSG_HEAD_SIZE || this->size_ > MAX_MSG_SIZE) {
		return -1;
	}

	if (str.size() < this->size_) {
		return 0;
	}

	this->content_ = str.substr(MSG_HEAD_SIZE, this->size_ - MSG_HEAD_SIZE);
	return this->size_;
}

