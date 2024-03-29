#pragma warning(disable: 4996)

#include "CwServerSocketUdp.h"

#include "BaseCWServerException.h"

CwServerSocketUdp::CwServerSocketUdp()
{
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_socket == INVALID_SOCKET) {
		std::string errorMsg = "CwServerSocketUdp.socket failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWServerException(errorMsg);
	}
}



CwServerSocketUdp::~CwServerSocketUdp()
{
	closesocket(m_socket);
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
		std::string errorMsg = "CwServerSocketUdp.bind failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWServerException(errorMsg);
	}
}
