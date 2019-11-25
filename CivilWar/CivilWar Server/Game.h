#pragma once

#include "Serializer.h"
#include "Server.h"
#include "CivilWar.h"

class Game
{
public:
	Game();
	~Game();

	// methods
	void initAll();
	void launchServer();
	void waitForClients();
	void start();
	void handleState();
	void recvMsgsAndProcess();

	bool isRunning() const { return m_is_running; }

private:
	//variables
	Serializer* m_serializer;
	Server* m_server;
	CivilWar* m_cw;

	bool m_is_running;

	char m_gameState;
	char m_advancedGameState;


	// methods
	void handleBeforeBattle();
	void handleBattleState();
};
