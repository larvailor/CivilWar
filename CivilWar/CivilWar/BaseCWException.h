#pragma once

#include <string>

class BaseCWException
{
public:
	BaseCWException(const std::string& msg) : m_msg(msg) { }

	std::string getMsg() { return m_msg; }

private:
	std::string m_msg;
};
