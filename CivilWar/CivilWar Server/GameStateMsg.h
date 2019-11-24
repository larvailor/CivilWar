#pragma once

#include "Msg.h"
#include "MsgTypes.h"

class GameStateMsg : public Msg
{
public:
	GameStateMsg(char gameState, char advancedInfo = NULL) :
		m_gameState(gameState),
		m_advancedInfo(advancedInfo),
		Msg(GAME_STATE_MSG_TYPE, NULL, NULL)
	{

	}



	// Message structure in bytes:
	// [0] - msg type
	// [1] - game state
	// [2] - advanced info
	void create(void* CWstruct) final
	{
		try {
			setMsgType(m_msg);
			setAdvancedType(m_msg, m_gameState);
			setAdvancedType(m_msg, m_advancedInfo);
		}
		catch (std::exception e) {
			throw e;
		}
	}

private:
	// variables
	char m_gameState;
	char m_advancedInfo;



	// methods
	void setMsgData(std::vector<char>& msg, void* CWstruct) final { } // not in use
};
