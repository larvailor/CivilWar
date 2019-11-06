#include "Game.h"

Game::Game() :
	m_gameState(BEFORE_BATTLE),
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
}



void Game::handleState()
{
	switch (m_gameState)
	{
	case BEFORE_BATTLE:
		handleBeforeBattle();
		break;
	case BATTLE:
		break;
	case AFTER_BATTLE:
		break;
	}
}



void Game::handleBeforeBattle()
{
	// create threads
	// send start msg to both clients
	// sleep for 3 sec
	m_server->sendBeforeBattleMsg(
		m_serializer->createGreenSoldierMsg(m_cw->getGreenSoldier()),
		m_serializer->createBlueSoldierMsg(m_cw->getBlueSoldier())
	);

}
