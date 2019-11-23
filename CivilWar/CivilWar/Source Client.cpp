#pragma comment(lib, "ws2_32.lib")

#include "BaseCWException.h"

#include "Config.h"
#include "CGame.h"

#include <iostream>

int main()
{
	CGame* game = new CGame();
	try {
		game->initAll();
		game->connectToCWServer(SERVER_IP, SERVER_PORT);
		game->start();
		while (game->isRunning()) {
			game->recvDataAndUpdate();
		}
	}
	catch (BaseCWException e) {
		// handle exception TBD
		return 1;
	}

	delete(game);

	return 0;
}
