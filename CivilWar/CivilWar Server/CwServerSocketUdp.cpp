#include "CwServerSocketUdp.h"

CwServerSocketUdp::CwServerSocketUdp()
{
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_socket == INVALID_SOCKET) {
		throw BaseCWServerException("CwServerSocketUdp.socket failed with error: " + WSAGetLastError());
	}
}



CwServerSocketUdp::~CwServerSocketUdp()
{
	int iResult = closesocket(m_socket);
	if (iResult == SOCKET_ERROR) {
		throw BaseCWServerException("CwServerSocketUdp.closesocket failed with error: " + WSAGetLastError());
	}
}



void CwServerSocketUdp::setSockAddr(const char* ip, int port)
{
	m_socketAddr.sin_addr.s_addr = inet_addr(ip);
	m_socketAddr.sin_family = AF_INET;
	m_socketAddr.sin_port = htons(port);
}



void CwServerSocketUdp::bindSocket()
{
	int iResult = bind(m_socket, (SOCKADDR*)&m_socketAddr, sizeof(m_socketAddr));
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = "CwServerSocketUdp.bind failed with error: " + WSAGetLastError();
		iResult = closesocket(m_socket);
		if (iResult == SOCKET_ERROR) {
			errorMsg += "\nSocketUDP.closesocket failed with error: " + WSAGetLastError();
		}
		throw BaseCWServerException(errorMsg);
	}
}
