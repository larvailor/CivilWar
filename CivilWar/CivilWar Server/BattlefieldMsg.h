#pragma once

#include "Msg.h"
#include "MsgTypes.h"
#include "ModelsAsDataTypes.h"

class BattlefieldMsg : public Msg
{
public:
	BattlefieldMsg() :
		Msg(BATTLEFIELD_MSG_TYPE, 1, BATTLEFIELD_STRUCT_SIZE)
	{

	}



	// Message structure in bytes:
	// [0] - msg type
	// [1] - advanced type
	// [2] - number of objects
	// bytes 3, 4, 5, 6 holds struct size
	// [3] - number of thousands
	// [4] - number of hundreds
	// [5] - number of tens
	// [6] - number of units
	// [...] - data
	void create(void* CWstruct) final
	{
		try {
			setMsgType(m_msg);
			setAdvancedType(m_msg, -1);
			setMsgNObjects(m_msg);
			setMsgStructSize(m_msg);
			setMsgData(m_msg, CWstruct);
		}
		catch (std::exception e) {
			throw e;
		}
	}


private:
	void setMsgData(std::vector<char>& msg, void* CWstruct) final
	{
		auto battlefield = static_cast<BattlefieldStruct*>(CWstruct);

		char* buffer = new char[m_structSize];
		memcpy(buffer, &(*battlefield), m_structSize);
		for (auto i = 0; i < m_structSize; i++) {
			msg.push_back(buffer[i]);
		}

		delete[](buffer);
	}
};