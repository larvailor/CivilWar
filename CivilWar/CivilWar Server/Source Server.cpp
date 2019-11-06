#pragma comment(lib, "ws2_32.lib") 

#include "BaseCWServerException.h"

#include "Config.h"
#include "Server.h"
#include "Game.h"

#include <iostream>


//#include "SoldierMsg.h"
int main()
{
	//struct soldier greenSoldier;
	//Point p = { 123, 321 };
	//greenSoldier.center = p;
	//greenSoldier.health = 3;
	//greenSoldier.radius = 4;
	//SoldierMsg* msg = new SoldierMsg();
	//std::vector<char> m = msg->create(&greenSoldier);

	Server* server = new Server();

	// gameloop
	Game* game = new Game();
	try {
		game->initAll();
		game->launchServer();
		game->waitForClients();
		game->start();
		while (game->isRunning()) {
			// get
			// calculate
			// send 
			game->handleState();
		}
	}
	catch (BaseCWServerException e) {
		std::cout << "Server failed with error:\n" << e.getMsg() << std::endl;
	}
	catch (std::exception e) {
		std::cout << "Server failed with error:\n" << e.what() << std::endl;
	}

	delete(server);
	delete(game);
	return 0;
}
