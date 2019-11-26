#ifndef UNICODE
#define UNICODE
#endif

#include "CGame.h"

#include "CGameState.h"

#include <vector>

CGame::CGame() :
	m_window(nullptr),
	m_isRunning(false),
	m_gameState(NULL),
	m_advancedGameState(NULL),
	m_wndThr(nullptr),
	m_drawThr(nullptr)
{
	m_network = new Network();
	m_serializer = new CSerializer();
}



CGame::~CGame()
{
	delete(m_serializer);
	delete(m_network);
	delete(m_window);
}



void CGame::initAll(HINSTANCE hInstance, int nCmdShow)
{
	m_window = new CWindow(m_serializer, hInstance, nCmdShow);
}



void CGame::connectToCWServer(const char* ip, int port)
{
	m_network->connectToCWServer(ip, port);
}



void CGame::start()
{
	m_isRunning = true;
}



void CGame::recvDataAndUpdate()
{
	std::vector<char> gameStateMsg = m_network->recvMsg();
	m_serializer->translateGameStateMsg(gameStateMsg, m_gameState, m_advancedGameState);

	switch (m_gameState) {
	case BEFORE_BATTLE_STATE:
		recvBeforeBattleMsg();
		break;
	case BATTLE_STATE:
		recvBattleMsg();
		break;
	case AFTER_BATTLE_STATE:
		break;
	}
}



void CGame::recvBeforeBattleMsg()
{
	std::vector<char> battlefieldMsg = m_network->recvMsg();
	m_serializer->translateMsg(battlefieldMsg);

	std::vector<char> greenSoldierMsg = m_network->recvMsg();
	m_serializer->translateMsg(greenSoldierMsg);

	std::vector<char> blueSoldierMsg = m_network->recvMsg();
	m_serializer->translateMsg(blueSoldierMsg);
}



void CGame::recvBattleMsg()
{
	std::vector<char> greenSoldierMsg = m_network->recvMsg();
	m_serializer->translateMsg(greenSoldierMsg);

	std::vector<char> blueSoldierMsg = m_network->recvMsg();
	m_serializer->translateMsg(blueSoldierMsg);

	std::vector<char> greenBulletsMsg = m_network->recvMsg();
	m_serializer->translateMsg(greenBulletsMsg);

	std::vector<char> blueBulletsMsg = m_network->recvMsg();
	m_serializer->translateMsg(blueBulletsMsg);
}



void CGame::sendClientData()
{
	if (m_window->getCursorX() != -1 && m_window->getCursorY() != -1) {
		m_network->sendMoveAndFireMsg(
			m_serializer->createMoveAndFireMsg(
				m_window->getPressedKey(),
				m_window->getCursorX(),
				m_window->getCursorY()
			)
		);
	}
	else {
		m_network->sendMoveMsg(
			m_serializer->createMoveMsg(
				m_window->getPressedKey()
			)
		);
	}

	m_window->dropPressedKey();
	m_window->dropCursor();
}



void CGame::handleState()
{
	switch (m_gameState) {
	case BEFORE_BATTLE_STATE:
		handleBeforeBattleState();
		break;
	case BATTLE_STATE:
		handleBattleState();
		break;
	case AFTER_BATTLE_STATE:
		handleAfterBattleState();
		break;
	}
}



void CGame::handleBeforeBattleState()
{
	m_wndThr = new std::thread(&CGame::windowThread, this);
	m_drawThr = new std::thread(&CGame::drawThread, this);
}



void CGame::handleBattleState()
{
	// TBD
}



void CGame::handleAfterBattleState()
{
	m_wndThr->join();
	m_drawThr->join();
	m_isRunning = false;
}



void CGame::windowThread()
{
	BattlefieldStruct* tmpBattlefield = m_serializer->getBattlefieldStruct();
	BOOL createResult = m_window->create(
		L"CivilWar",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		static_cast<int>(tmpBattlefield->width),
		static_cast<int>(tmpBattlefield->height)
	);
	delete(tmpBattlefield);
	if (!createResult) {
		MessageBox(NULL, L"Create window failed", L"Error", NULL);
		m_isRunning = false;
		return;
	}

	ShowWindow(m_window->getWindow(), m_window->getNCmdShow());

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}



void CGame::drawThread()
{
	while (m_isRunning) {
		InvalidateRect(m_window->getWindow(), NULL, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}
