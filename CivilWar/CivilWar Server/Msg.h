#pragma once

#include <vector>

class Msg
{
public:
	Msg(char msgType, char nObject, int size):
		m_msgType(msgType),
		m_nObjects(nObject),
		m_structSize(size)
	{

	}

	virtual void create(void* CWstruct) = 0;

	std::vector<char> getMsg() const { return m_msg; }

protected:
	// variables
	char m_msgType;
	char m_nObjects;
	int m_structSize;
	std::vector<char> m_msg;

	
	// methods
	void setMsgType(std::vector<char> &msg)
	{
		msg.push_back(m_msgType);
	}

	void setMsgNObjects(std::vector<char> &msg)
	{
		msg.push_back(m_nObjects);
	}

	void setMsgStructSize(std::vector<char> &msg)
	{
		char* structSizeStr = intToStr(m_structSize);
		for (auto i = 0; i < 4; i++) {
			msg.push_back(structSizeStr[i]);
		}
	}

	void setAdvancedType(std::vector<char>& msg, char advancedType)
	{
		msg.push_back(advancedType);
	}

	virtual void setMsgData(std::vector<char> &msg, void* CWstruct) = 0;

private:
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
		sizeStr[0] = thousands;
		sizeStr[1] = hundreds;
		sizeStr[2] = tens;
		sizeStr[3] = units;
		sizeStr[4] = 0;
		return sizeStr;
	}
};
