#pragma once

#pragma warning(disable: 4996)

#include "CwClientSocketTcp.h"

#include "CMoveMsg.h"
#include "CMoveAndFireMsg.h"

#include <WinSock2.h>
#include <list>
#include <vector>

class Network
{
public:
	Network();
	~Network();

	void connectToCWServer(const char* ip, int port);
	std::vector<char> recvMsg();
	void sendMoveMsg(CMoveMsg* moveMsg);
	void sendMoveAndFireMsg(CMoveAndFireMsg* moveAndFireMsg);

private:
	// variables
	CwClientSocketTcp* m_socketTcp;



	// methods
	void initializeWinSock();
	void createSockets();
};
