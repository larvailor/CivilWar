#pragma once

#include "Msg.h"
#include "MsgTypes.h"
#include "ModelsAsDataTypes.h"

class BulletsMsg : public Msg
{
public:
	BulletsMsg(int bulletsCount, char bulletsColor) :
		Msg(BULLETS_MSG_TYPE, bulletsCount, BULLET_STRUCT_SIZE),
		m_bulletsColor(bulletsColor)
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
	void create(std::vector<BulletStruct> bullets)
	{
		try {
			setMsgType(m_msg);
			setAdvancedType(m_msg, m_bulletsColor);
			setMsgNObjects(m_msg);
			setMsgStructSize(m_msg);
			for (int i = 0; i < m_nObjects; i++) {
				setMsgData(m_msg, &bullets[i]);
			}
		}
		catch (std::exception e) {
			throw e;
		}
	}

	// do not use!!!
	void create(void* CWstruct) final { }

private:
	// variables
	char m_bulletsColor;


	// methods
	void setMsgData(std::vector<char>& msg, void* CWstruct) final
	{
		auto bullet = static_cast<BulletStruct*>(CWstruct);

		char* buffer = new char[m_structSize];
		memcpy(buffer, &(*bullet), m_structSize);
		for (auto i = 0; i < m_structSize; i++) {
			msg.push_back(buffer[i]);
		}

		delete[](buffer);
	}
};
