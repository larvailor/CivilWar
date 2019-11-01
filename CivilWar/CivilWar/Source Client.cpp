#pragma comment(lib, "ws2_32.lib")

#include "Network.h"

#include <iostream>

int main()
{
	Network* network = new Network();
	network->connectToCWServer();

	return 0;
}
