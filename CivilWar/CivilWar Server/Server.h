#pragma once

#include "Config.h"
#include "Game.h"

#include "BaseCWServerException.h"

#include "SocketTCP.h"
#include "SocketUDP.h"

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
	SocketTCP* m_socketTcp;
	SocketUDP* m_socketUdp;

	SOCKET m_greenSoldierSocket;
	SOCKET m_blueSoldierSocket;



	// methods
	void initializeWinSock();
	void createSockets();
	void initializeSockAddr(const char* ip, int port);
	void bindSockets();
};
