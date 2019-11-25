#include "CwClientSocketTcp.h"

#include "BaseCWException.h"

CwClientSocketTcp::CwClientSocketTcp()
{
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		std::string errorMsg = "CwClientSocketTcp.socket failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWException(errorMsg);
	}
}



CwClientSocketTcp::~CwClientSocketTcp()
{
	int iResult = closesocket(m_socket);
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = "CwClientSocketTcp.closesocket failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWException(errorMsg);
	}
}



void CwClientSocketTcp::connectToCwServer(const char* ip, int port)
{
	// initialize SOCKADDR_IN structure
	m_serverSocketAddr.sin_addr.s_addr = inet_addr(ip);
	m_serverSocketAddr.sin_family = AF_INET;
	m_serverSocketAddr.sin_port = htons(port);

	// connect
	int iResult = connect(m_socket, (SOCKADDR*)&m_serverSocketAddr, sizeof(m_serverSocketAddr));
	if (iResult != 0) {
		std::string errorMsg = "CwClientSocketTcp.connecToCwServer failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWException(errorMsg);
	}
}



void CwClientSocketTcp::recvMsgFromServer(char* buffer, int bufferSize, int &bytesReceived)
{
	bytesReceived = recv(m_socket, buffer, bufferSize, NULL);

	// send confirm to server
	char confirmBufferSize = 1;
	char* confirmBuffer = new char[confirmBufferSize];
	confirmBuffer[0] = 1;
	send(m_socket, confirmBuffer, confirmBufferSize, NULL);
}



int CwClientSocketTcp::sendMsgToServer(char* msg, size_t msgSize, int flags)
{
	int bytesSent;
	int bytesReceived;
	char confirmBufferSize = 1;
	char* confirmBuffer = new char[confirmBufferSize];
	for (int tries = 3; tries != 0; tries--) {
		bytesSent = send(m_socket, msg, msgSize, flags);

		// wait while server confirm msg
		bytesReceived = recv(m_socket, confirmBuffer, confirmBufferSize, NULL);
		if (bytesReceived != SOCKET_ERROR) {
			break;
		}
	}

	return bytesSent;
}
