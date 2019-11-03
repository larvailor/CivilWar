#pragma comment(lib, "ws2_32.lib")

#include "Config.h"
#include "Network.h"

#include <iostream>

int main()
{
	Network* network = new Network();
	connectToCwServer();
	try {
		network->connectToCWServer(SERVER_IP, SERVER_PORT);
	}
	catch (BaseCWException e) {
		// handle exception TBD
		return 1;
	}

	delete(network);

	return 0;
}
