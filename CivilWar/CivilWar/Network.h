#pragma once

#pragma warning(disable: 4996)

#include "Config.h"

#include "BaseCWException.h"

#include "CwClientSocketTcp.h"
#include "CwClientSocketUdp.h"

#include <WinSock2.h>
#include <list>

class Network
{
public:
	Network();
	~Network();

	void connectToCWServer(const char* ip, int port);

private:
	// variables
	CwClientSocketTcp* m_socketTcp;
	//CwClientSocketUdp* m_socketUdp;



	// methods
	void initializeWinSock();
	void createSockets();
};
