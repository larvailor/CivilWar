#pragma once

#include <WinSock2.h>

class CwServerSocketTcp
{
public:
	CwServerSocketTcp();
	~CwServerSocketTcp();

	SOCKET getSocket() const { return m_socket; }

	void setSockAddr(const char* ip, int port);
	void bindSocket();
	void doListen();
	SOCKET acceptConnection();

private:
	SOCKET m_socket;
	SOCKADDR_IN m_socketAddr;
};
