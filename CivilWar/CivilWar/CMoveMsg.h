#pragma once

#include "CMsgTypesToServer.h"

#include <vector>

class CMoveMsg
{
public:
	CMoveMsg() :
		m_msgType(MOVE_MSG)
	{

	}



	// Message structure in bytes:
	// [0] - msg type
	// [1] - pressed key
	void create(char pressedKey)
	{
		try {
			m_msg.push_back(m_msgType);
			m_msg.push_back(pressedKey);
		}
		catch (std::exception e) {
			throw e;
		}
	}

	std::vector<char> getMsg() const { return m_msg; }

private:
	// variables
	char m_msgType;
	std::vector<char> m_msg;
};
