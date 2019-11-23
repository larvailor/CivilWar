#pragma once

#include "CwServerSocketTcp.h"
#include "CwServerSocketUdp.h"

#include "BattlefieldMsg.h"
#include "SoldierMsg.h"

class Server
{
public:
	Server();
	~Server();
	 
	void start(const char* ip, int port);

	void waitForClients();

	void sendBeforeBattleMsg(BattlefieldMsg* battlefieldMsg, SoldierMsg* greenSoldierMsg, SoldierMsg* blueSoldierMsg);

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

	void sendBattlefieldMsg(BattlefieldMsg* battlefieldMsg);
	void sendSoldierMsg(SoldierMsg* soldierMsg);
};
