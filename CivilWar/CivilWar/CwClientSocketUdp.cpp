#pragma once
#pragma warning(disable: 4996)

#include "BaseCWException.h"

#include <WinSock2.h>

class CwServerSocketTcp
{
public:
	CwServerSocketTcp();
	~CwServerSocketTcp();

	SOCKET getSocket() const { return m_socket; }

	void setSockAddr(const char* ip, int port);
	void connectToCwServer();

private:
	SOCKET m_socket;
	SOCKADDR_IN m_socketAddr;
};
