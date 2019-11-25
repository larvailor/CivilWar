#pragma once

#include "Network.h"
#include "CSerializer.h"
#include "CWindow.h"

#include <thread>

class CGame
{
public:
	CGame();
	~CGame();

	void initAll(HINSTANCE hInstance, int nCmdShow);
	void connectToCWServer(const char* ip, int port);
	void start();
	bool isRunning() const { return m_isRunning; }

	void recvDataAndUpdate();
	void handleState();
	void draw();

private:
	// variables
	Network* m_network;
	CSerializer* m_serializer;
	CWindow* m_window;

	bool m_isRunning;

	char m_gameState;
	char m_advancedGameState;

	std::thread* m_wndThr;



	// methods
	void windowThread();
	void handleBeforeBattleState();
	void handleAfterBattleState();
};
