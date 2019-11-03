#pragma once

#include "CwServerSocketTcp.h"
#include "CwServerSocketUdp.h"

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
	void doListen();
};
