#pragma once
#pragma warning(disable: 4996)

#include "BaseCWServerException.h"

#include <WinSock2.h>

class SocketTCP
{
public:
	SocketTCP();
	~SocketTCP();

	SOCKET getSocket() const { return m_socket; }

	void setSockAddr(const char* ip, int port);
	void bindSocket();
	void doListen();

private:
	SOCKET m_socket;
	SOCKADDR_IN m_socketAddr;
};
