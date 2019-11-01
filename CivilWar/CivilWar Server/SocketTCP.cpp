#include "SocketTCP.h"

SocketTCP::SocketTCP()
{
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		throw BaseCWServerException("SocketTCP.socket failed with error: " + WSAGetLastError());
	}
}



SocketTCP::~SocketTCP()
{
	int iResult = closesocket(m_socket);
	if (iResult == SOCKET_ERROR) {
		throw BaseCWServerException("SocketTCP.closesocket failed with error: " + WSAGetLastError());
	}
}



void SocketTCP::setSockAddr(const char* ip, int port)
{
	m_socketAddr.sin_addr.s_addr = inet_addr(ip);
	m_socketAddr.sin_family = AF_INET;
	m_socketAddr.sin_port = htons(port);
}



void SocketTCP::bindSocket()
{
	int iResult = bind(m_socket, (SOCKADDR*)&m_socketAddr, sizeof(m_socketAddr));
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = "SocketTCP.bind failed with error: " + WSAGetLastError();
		iResult = closesocket(m_socket);
		if (iResult == SOCKET_ERROR) {
			errorMsg += "\nSocketTCP.closesocket failed with error: " + WSAGetLastError();
		}
		throw BaseCWServerException(errorMsg);
	}
}



void SocketTCP::doListen()
{
	int iResult = listen(m_socket, 0);
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = "SocketTCP.listen failed with error: " + WSAGetLastError();
		iResult = closesocket(m_socket);
		if (iResult == SOCKET_ERROR) {
			errorMsg += "\nSocketTCP.closesocket failed with error: " + WSAGetLastError();
		}
		throw BaseCWServerException(errorMsg);
	}
}


