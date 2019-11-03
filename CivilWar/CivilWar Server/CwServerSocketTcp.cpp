#include "CwServerSocketTcp.h"

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
	int iResult = closesocket(m_socket);
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = "CwServerSocketTcp.closesocket failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWServerException(errorMsg);
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
}
