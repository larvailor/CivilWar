#include "Server.h"

Server::Server() :
	m_socketTcp(nullptr),
	m_socketUdp(nullptr),
	m_greenSoldierSocket(0),
	m_blueSoldierSocket(0)
{

}



Server::~Server()
{
	delete(m_socketTcp);
	delete(m_socketUdp);
}



void Server::start(const char* ip, int port)
{
	std::cout << "SERVER STARTUP" << std::endl;

	initializeWinSock();
	createSockets();
	initializeSockAddr(ip, port);
	bindSockets();

	std::cout << "SERVER STARTED\n" << std::endl;
}



void Server::initializeWinSock()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int iResult = WSAStartup(wVersionRequested, &wsaData);
	if (iResult != 0) {
		throw BaseCWServerException("WSAStartup failed with error: " + WSAGetLastError());
	}
	
	std::cout << "  |  WSAStartup success" << std::endl;
}



void Server::createSockets()
{
	// create TCP socket
	try {
		m_socketTcp = new CwServerSocketTcp();
	}
	catch (BaseCWServerException e) {
		WSACleanup();
		throw e;
	}

	std::cout << "  |  tcp socket created" << std::endl;

	// create UDP socket
	try {
		m_socketUdp = new CwServerSocketUdp();
	}
	catch (BaseCWServerException e) {
		WSACleanup();
		throw e;
	}

	std::cout << "  |  udp socket created" << std::endl;
}



void Server::initializeSockAddr(const char* ip, int port)
{
	// initialize TCP socket addr structure
	m_socketTcp->setSockAddr(ip, port);
	std::cout << "  |  tcp socket addr initialized" << std::endl;

	// initialize UDP socket addr structure
	m_socketUdp->setSockAddr(ip, port);
	std::cout << "  |  udp socket addr initialized" << std::endl;
}



void Server::bindSockets()
{
	// bind TCP socket
	try {
		m_socketTcp->bindSocket();
	}
	catch (BaseCWServerException e) {
		WSACleanup();
		throw e;
	}

	std::cout << "  |  bind TCP success" << std::endl;

	// bind UDP socket
	try {
		m_socketUdp->bindSocket();
	}
	catch (BaseCWServerException e) {
		WSACleanup();
		throw e;
	}

	std::cout << "  |  bind UDP success" << std::endl;
}



void Server::waitClientsConnection()
{
	SOCKET acceptSocket;
}
