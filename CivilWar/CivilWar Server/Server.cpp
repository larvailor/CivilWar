#include "Server.h"

Server::Server() :
	m_socketTcp(nullptr),
	m_socketUdp(nullptr)
{

}



Server::~Server()
{
	delete(m_socketTcp);
	delete(m_socketUdp);
}



void Server::start()
{
	std::cout << "SERVER STARTUP" << std::endl;

	initializeWinSock();
	createSockets();
	initializeSockAddr();
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
		m_socketTcp = new SocketTCP();
	}
	catch (BaseCWServerException e) {
		WSACleanup();
		throw e;
	}

	std::cout << "  |  tcp socket created" << std::endl;

	// create UDP socket
	try {
		m_socketUdp = new SocketUDP();
	}
	catch (BaseCWServerException e) {
		WSACleanup();
		throw e;
	}

	std::cout << "  |  udp socket created" << std::endl;
}



void Server::initializeSockAddr()
{
	// initialize TCP socket addr structure
	m_socketTcp->setSockAddr(SERVER_IP, SERVER_PORT);
	std::cout << "  |  tcp socket addr initialized" << std::endl;

	// initialize UDP socket addr structure
	m_socketUdp->setSockAddr(SERVER_IP, SERVER_PORT);
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
