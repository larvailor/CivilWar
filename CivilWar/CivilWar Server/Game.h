#pragma once

#include "Config.h"
#include "Serializer.h"
#include "Server.h"
#include "CivilWar.h"

#include "BaseCWServerException.h"

enum GameState {
	BEFORE_BATTLE,
	BATTLE,
	AFTER_BATTLE
};

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

	GameState getGameState() const { return m_gameState; }
	bool isRunning() const { return m_is_running; }
	void setGameState(GameState gameState) { m_gameState = gameState; }

private:
	//variables
	GameState m_gameState;
	Serializer* m_serializer;
	Server* m_server;
	CivilWar* m_cw;

	bool m_is_running;



	// methods
	void handleBeforeBattle();
};
