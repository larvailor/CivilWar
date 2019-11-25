#pragma once

#include "CMsgTypesToServer.h"

#include <vector>

class CMoveAndFireMsg
{
public:
	CMoveAndFireMsg() :
		m_msgType(MOVE_AND_FIRE_MSG)
	{

	}



	// Message structure in bytes:
	// [0] - msg type
	// [1] - pressed key
	// [2, 3, 4, 5] - mouse x (thousands, hundreeds, tens, units)
	// [6, 7, 8, 9] - mouse y
	void create(char pressedKey, int mouseX, int mouseY)
	{
		try {
			m_msg.push_back(m_msgType);
			m_msg.push_back(pressedKey);
			char* buffer = intToStr(mouseX);
			for (auto i = 0; i < 4; i++) {
				m_msg.push_back(buffer[i]);
			}
			buffer = intToStr(mouseY);
			for (auto i = 0; i < 4; i++) {
				m_msg.push_back(buffer[i]);
			}
			delete(buffer);
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



	// methods
	char* intToStr(int size)
	{
		char thousands = size / 1000;
		size -= thousands * 1000;
		char hundreds = size / 100;
		size -= hundreds * 100;
		char tens = size / 10;
		size -= tens * 10;
		char units = size;

		char* sizeStr = new char[5];
		//sizeStr[0] = thousands + 0x30;
		//sizeStr[1] = hundreds + 0x30;
		//sizeStr[2] = tens + 0x30;
		//sizeStr[3] = units + 0x30;
		//sizeStr[4] = 0;
		sizeStr[0] = thousands;
		sizeStr[1] = hundreds;
		sizeStr[2] = tens;
		sizeStr[3] = units;
		sizeStr[4] = 0;
		return sizeStr;
	}
};
