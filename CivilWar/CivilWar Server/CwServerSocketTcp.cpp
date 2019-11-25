#pragma warning(disable: 4996)

#include "CwServerSocketTcp.h"

#include "BaseCWServerException.h"

CwServerSocketTcp::CwServerSocketTcp()
{
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		std::string errorMsg = "CwServerSocketTcp.socket failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWServerException(errorMsg);
	}
}



CwServerSocketTcp::~CwServerSocketTcp()
{
	closesocket(m_socket);
}



void CwServerSocketTcp::setSockAddr(const char* ip, int port)
{
	m_socketAddr.sin_addr.s_addr = inet_addr(ip);
	m_socketAddr.sin_family = AF_INET;
	m_socketAddr.sin_port = htons(port);
}



void CwServerSocketTcp::bindSocket()
{
	int iResult = bind(m_socket, (SOCKADDR*)&m_socketAddr, sizeof(m_socketAddr));
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = "CwServerSocketTcp.bind failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWServerException(errorMsg);
	}
}



void CwServerSocketTcp::doListen()
{
	int iResult = listen(m_socket, 0);
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = "CwServerSocketTcp.listen failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWServerException(errorMsg);
	}
}



SOCKET CwServerSocketTcp::acceptConnection()
{
	int socketAddrSize = sizeof(m_socketAddr);
	SOCKET acceptSocket = accept(m_socket, (SOCKADDR*)&m_socketAddr, &socketAddrSize);
	if (acceptSocket == INVALID_SOCKET) {
		std::string errorMsg = "CwServerSocketTcp.accept failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWServerException(errorMsg);
	}

	return acceptSocket;
}



int CwServerSocketTcp::sendMsgToClient(SOCKET clientSocket, char* msg, size_t msgSize, int flags)
{
	int bytesSent;
	int bytesReceived;
	char confirmBufferSize = 1;
	char* confirmBuffer = new char[confirmBufferSize];
	for (int tries = 3; tries != 0; tries--) {
		bytesSent = send(clientSocket, msg, msgSize, flags);

		// wait while client confirm msg
		bytesReceived = recv(clientSocket, confirmBuffer, confirmBufferSize, NULL); 
		if (bytesReceived != SOCKET_ERROR) {
			break;
		}
	}
	
	return bytesSent;
}



void CwServerSocketTcp::recvMsgFromClient(SOCKET clientSocket, char* buffer, int bufferSize, int& bytesReceived)
{
	bytesReceived = recv(clientSocket, buffer, bufferSize, NULL);

	// send confirm to client
	char confirmBufferSize = 1;
	char* confirmBuffer = new char[confirmBufferSize];
	confirmBuffer[0] = 1;
	send(clientSocket, confirmBuffer, confirmBufferSize, NULL);
}