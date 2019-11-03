#include "CwClientSocketTcp.h"

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


