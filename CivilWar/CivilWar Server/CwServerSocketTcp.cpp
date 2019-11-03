#include "CwServerSocketTcp.h"

CwServerSocketTcp::CwServerSocketTcp()
{
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		throw BaseCWServerException("CwServerSocketTcp.socket failed with error: " + WSAGetLastError());
	}
}



CwServerSocketTcp::~CwServerSocketTcp()
{
	int iResult = closesocket(m_socket);
	if (iResult == SOCKET_ERROR) {
		throw BaseCWServerException("CwServerSocketTcp.closesocket failed with error: " + WSAGetLastError());
	}
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
		std::string errorMsg = "CwServerSocketTcp.bind failed with error: " + WSAGetLastError();
		iResult = closesocket(m_socket);
		if (iResult == SOCKET_ERROR) {
			errorMsg += "\nSocketTCP.closesocket failed with error: " + WSAGetLastError();
		}
		throw BaseCWServerException(errorMsg);
	}
}



void CwServerSocketTcp::doListen()
{
	int iResult = listen(m_socket, 0);
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = "CwServerSocketTcp.listen failed with error: " + WSAGetLastError();
		iResult = closesocket(m_socket);
		if (iResult == SOCKET_ERROR) {
			errorMsg += "\nSocketTCP.closesocket failed with error: " + WSAGetLastError();
		}
		throw BaseCWServerException(errorMsg);
	}
}


