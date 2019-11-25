#pragma comment(lib, "ws2_32.lib")

#include "BaseCWException.h"

#include "Config.h"
#include "CGame.h"

#include <Windows.h>
#include <iostream>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
	CGame* game = new CGame();
	try {
		game->initAll(hInstance, nCmdShow);
		game->connectToCWServer(SERVER_IP, SERVER_PORT);
		game->start();
		while (game->isRunning()) {
			game->recvDataAndUpdate();
			game->handleState();
			game->sendClientData();
		}
	}
	catch (BaseCWException e) {
		// handle exception TBD
		return 1;
	}

	delete(game);

	return 0;
}
