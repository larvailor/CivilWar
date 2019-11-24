#include "Game.h"

#include "BaseCWServerException.h"

#include "Config.h"
#include "GameState.h"

Game::Game() :
	m_gameState(NULL),
	m_advancedGameState(NULL),
	m_is_running(false)
{
	m_server = new Server();
	m_serializer = new Serializer();
	m_cw = new CivilWar();
}



Game::~Game()
{
	delete(m_cw);
	delete(m_serializer);
	delete(m_server);
}



void Game::initAll()
{
	m_cw->initAll();
	m_serializer->init(m_cw->getBattlefield(), m_cw->getGreenSoldier(), m_cw->getBlueSoldier());
}



void Game::launchServer()
{
	m_server->start(SERVER_IP, SERVER_PORT);
}



void Game::waitForClients()
{
	m_server->waitForClients();
}



void Game::start()
{
	m_is_running = true;
	m_gameState = BEFORE_BATTLE_STATE;
}



void Game::handleState()
{
	switch (m_gameState)
	{
	case BEFORE_BATTLE_STATE:
		handleBeforeBattle();
		break;
	case BATTLE_STATE:
		break;
	case AFTER_BATTLE_STATE:
		break;
	}
}



void Game::handleBeforeBattle()
{
	m_server->sendGameStateMsg(m_serializer->createGameStateMsg(m_gameState, m_advancedGameState));

	m_server->sendBeforeBattleMsg(
		m_serializer->createBattlefieldMsg(m_cw->getBattlefield()),
		m_serializer->createGreenSoldierMsg(m_cw->getGreenSoldier()),
		m_serializer->createBlueSoldierMsg(m_cw->getBlueSoldier())
	);

	m_gameState = BATTLE_STATE;
}
