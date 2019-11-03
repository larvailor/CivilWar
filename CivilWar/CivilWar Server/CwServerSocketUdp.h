#pragma once

#include <WinSock2.h>

class CwServerSocketUdp
{
public:
	CwServerSocketUdp();
	~CwServerSocketUdp();

	SOCKET getSocket() const { return m_socket; }

	void setSockAddr(const char* ip, int port);
	void bindSocket();

private:
	SOCKET m_socket;
	SOCKADDR_IN m_socketAddr;
};
