#pragma comment(lib, "ws2_32.lib") 

#include "Config.h"
#include "Game.h"
#include "Server.h"

#include <iostream>

struct battlefield battlefield;
struct soldier greenSoldier;
struct soldier blueSoldier;

// server entry point
int main()
{
	Server* server = new Server();
	try {
		server->start();
		server->waitClientsConnection();
	}
	catch (BaseCWServerException e) {
		std::cout << "Server failed with error:\n" << e.getMsg() << std::endl;
	}

	delete(server);
	return 0;
}
