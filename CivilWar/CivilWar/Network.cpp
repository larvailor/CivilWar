#include "Network.h"

Network::Network()
{
	initializeWinSock();
	createSocket();
	initializeSockAddr();
	//bindSocket();
}



Network::~Network()
= default;



void Network::initializeWinSock()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int iResult = WSAStartup(wVersionRequested, &wsaData);
	if (iResult != 0) {
		throw(BaseCWException("WSAStartup failed with error: " + WSAGetLastError()));
	}
}



void Network::createSocket()
{
	m_listenClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_listenClientSocket == INVALID_SOCKET) {
		WSACleanup();
		throw(BaseCWException("socket failed with error: " + WSAGetLastError()));
	}
}



void Network::initializeSockAddr()
{
	m_serverAddrSize = sizeof(m_serverAddr);

	m_serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(SERVER_PORT);
}



void Network::bindSocket()
{
	/*int iResult = bind(m_listenClientSocket, (SOCKADDR*)&m_serverAddr, m_serverAddrSize);
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = "bind failed with error: " + WSAGetLastError();
		iResult = closesocket(m_listenClientSocket);
		if (iResult == SOCKET_ERROR) {
			errorMsg += "\nclosesocket failed with error: " + WSAGetLastError();
		}
		WSACleanup();
		throw(BaseCWException(errorMsg));
	}*/
}



void Network::connectToCWServer()
{
	int connectBuffSize = 2;
	char connectBuff[2] = "Y";

	int iResult = sendto(m_listenClientSocket, connectBuff, connectBuffSize, 0, (SOCKADDR*)&m_serverAddr, m_serverAddrSize);

}
