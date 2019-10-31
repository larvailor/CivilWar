#pragma once

#include <string>

class BaseCWServerException
{
public:
	BaseCWServerException(const std::string& msg) : m_msg(msg) { }

	std::string getMsg() { return m_msg; }

private:
	std::string m_msg;
};
