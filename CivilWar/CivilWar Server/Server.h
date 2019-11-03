#pragma once

#include "Config.h"
#include "Game.h"

#include "BaseCWServerException.h"

#include "CwServerSocketTcp.h"
#include "CwServerSocketUdp.h"

#include <iostream>
#include <WinSock2.h>

class Server
{
public:
	Server();
	~Server();

	void start(const char* ip, int port);

	void waitClientsConnection();

private:
	// variables
	CwServerSocketTcp* m_socketTcp;
	CwServerSocketUdp* m_socketUdp;

	SOCKET m_greenSoldierSocket;
	SOCKET m_blueSoldierSocket;



	// methods
	void initializeWinSock();
	void createSockets();
	void initializeSockAddr(const char* ip, int port);
	void bindSockets();
};
