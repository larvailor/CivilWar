#pragma once
#pragma warning(disable: 4996)

#include <WinSock2.h>

class CwClientSocketTcp
{
public:
	CwClientSocketTcp();
	~CwClientSocketTcp();

	SOCKET getSocket() const { return m_socket; } 

	void connectToCwServer(const char* ip, int port);
	void recvMsgFromServer(char* buffer, int bufferSize, int &bytesReceived);

	int sendMsgToServer(char* msg, size_t msgSize, int flags);

private:
	// variables
	SOCKET m_socket;
	SOCKADDR_IN m_serverSocketAddr;
};
