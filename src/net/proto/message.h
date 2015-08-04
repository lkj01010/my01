#pragma once
#include <string>
#include <stdint.h>


namespace net
{
static const uint8_t MSG_HEAD_SIZE = 9;

class message
{
public:
	message();

	message(uint16_t cmd, uint8_t encrypt, uint16_t param, const std::string& content);


	std::string serialize_as_string() const;

	void serialize_to_string(std::string& str) const;

	int parse_from_string(const std::string& str);

	void set_command(uint16_t cmd) { cmd_ = cmd; }
	uint16_t get_command() const { return cmd_; }

	void set_encrypt_type(uint8_t encrypt) { encrypt_ = encrypt; }
	uint8_t get_encrypt_type() const { return encrypt_; }

	uint16_t get_size() const { return size_; }

	void set_param(uint16_t param) { param_ = param; }
	uint16_t get_param() const { return param_; }

	void set_content(const std::string& content) { content_ = content; }
	const std::string& get_content() const { return content_; }
private:
	std::string serialize_head_as_string() const;
	void serialize_head_to_string(std::string& str) const;
	int parse_head_from_string(const std::string& str);

private:
	mutable uint16_t pad_;
	mutable uint16_t size_;
	uint16_t cmd_;
	uint8_t  encrypt_;
	uint16_t param_;
	std::string content_;

};

}