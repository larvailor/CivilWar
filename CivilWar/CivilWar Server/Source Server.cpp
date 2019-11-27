#pragma comment(lib, "ws2_32.lib") 

#include "BaseCWServerException.h"

#include "Config.h"
#include "Server.h"
#include "Game.h"

#include <iostream>

int main()
{
	// gameloop
	Game* game = new Game();
	try {
		game->initAll();
		game->launchServer();
		game->waitForClients();
		game->start();
		while (game->isRunning()) {
			game->handleState();
			game->recvMsgsAndProcess();
		}
	}
	catch (BaseCWServerException e) {
		std::cout << "Server failed with error:\n" << e.getMsg() << std::endl;
	}
	catch (std::exception e) {
		std::cout << "Server failed with error:\n" << e.what() << std::endl;
	}

	delete(game);
	return 0;
}
