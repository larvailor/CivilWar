#include "Server.h"

#include "BaseCWServerException.h"

#include <string>
#include <iostream>

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
	doListen();

	std::cout << "SERVER STARTED\n" << std::endl;
}



void Server::initializeWinSock()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int iResult = WSAStartup(wVersionRequested, &wsaData);
	if (iResult != 0) {
		std::string errorMsg = "WSAStartup failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWServerException(errorMsg);
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



void Server::doListen()
{
	try {
		m_socketTcp->doListen();
	}
	catch (BaseCWServerException e) {
		WSACleanup();
		throw e;
	}
}



void Server::waitForClients()
{
	std::cout << "Waiting for clients..." << std::endl;

	SOCKET acceptSocket;
	while (m_greenSoldierSocket == 0 || m_blueSoldierSocket == 0) {
		try {
			acceptSocket = m_socketTcp->acceptConnection();
			m_greenSoldierSocket == 0 ? m_greenSoldierSocket = acceptSocket : m_blueSoldierSocket = acceptSocket;
			
			std::cout << "Client conected!" << std::endl;
		}
		catch (BaseCWServerException e) {
			WSACleanup();
			throw e;
		}
	}
}



void Server::sendBeforeBattleMsg(BattlefieldMsg* battlefieldMsg, SoldierMsg* greenSoldierMsg, SoldierMsg* blueSoldierMsg)
{
	// battlefield
	try {
		sendBattlefieldMsg(battlefieldMsg);
	}
	catch (BaseCWServerException e) {
		std::cout << e.getMsg() << std::endl;
	}

	// greeen soldier
	try {
		sendSoldierMsg(greenSoldierMsg);
	}
	catch (BaseCWServerException e) {
		std::cout << e.getMsg() << std::endl;
	}

	// blue soldier
	try {
		sendSoldierMsg(blueSoldierMsg);
	}
	catch (BaseCWServerException e) {
		std::cout << e.getMsg() << std::endl;
	}
}



void Server::sendBattleMsg(SoldierMsg* greenSoldierMsg, SoldierMsg* blueSoldierMsg)
{
	// greeen soldier
	try {
		sendSoldierMsg(greenSoldierMsg);
	}
	catch (BaseCWServerException e) {
		std::cout << e.getMsg() << std::endl;
	}

	// blue soldier
	try {
		sendSoldierMsg(blueSoldierMsg);
	}
	catch (BaseCWServerException e) {
		std::cout << e.getMsg() << std::endl;
	}
}



void Server::sendBattlefieldMsg(BattlefieldMsg* battlefieldMsg)
{
	std::vector<char> msg = battlefieldMsg->getMsg();
	delete(battlefieldMsg);

	int bytesSent = 0;
	std::string errorMsg;
	// send to green player
	bytesSent = m_socketTcp->sendMsgToClient(m_greenSoldierSocket, msg.data(), msg.size(), NULL);
	if (bytesSent == SOCKET_ERROR) {
		errorMsg += "sendBattlefieldMsg to green player failed with error: " + std::to_string(WSAGetLastError());
	}

	// send to second player
	bytesSent = m_socketTcp->sendMsgToClient(m_blueSoldierSocket, msg.data(), msg.size(), NULL);
	if (bytesSent == SOCKET_ERROR) {
		errorMsg += "sendBattlefieldMsg msg to blue player failed with error: " + std::to_string(WSAGetLastError());
	}

	if (errorMsg.length() != 0) {
		throw BaseCWServerException(errorMsg);
	}
}



void Server::sendSoldierMsg(SoldierMsg* soldierMsg)
{
	std::vector<char> msg = soldierMsg->getMsg();
	delete(soldierMsg);

	int bytesSent = 0;
	std::string errorMsg;
	// send to green player
	bytesSent = m_socketTcp->sendMsgToClient(m_greenSoldierSocket, msg.data(), msg.size(), NULL);
	if (bytesSent == SOCKET_ERROR) {
		errorMsg += "sendSoldierMsg msg to green player failed with error: " + std::to_string(WSAGetLastError());
	}

	// send to second player
	bytesSent = m_socketTcp->sendMsgToClient(m_blueSoldierSocket, msg.data(), msg.size(), NULL);
	if (bytesSent == SOCKET_ERROR) {
		errorMsg += "sendSoldierMsg msg to blue player failed with error: " + std::to_string(WSAGetLastError());
	}

	if (errorMsg.length() != 0) {
		throw BaseCWServerException(errorMsg);
	}
}



void Server::sendGameStateMsg(GameStateMsg* gameStateMsg)
{
	std::vector<char> msg = gameStateMsg->getMsg();
	delete(gameStateMsg);

	int bytesSent = 0;
	std::string errorMsg;
	// send to green player
	bytesSent = m_socketTcp->sendMsgToClient(m_greenSoldierSocket, msg.data(), msg.size(), NULL);
	if (bytesSent == SOCKET_ERROR) {
		errorMsg += "sendGameStateMsg msg to green player failed with error: " + std::to_string(WSAGetLastError());
	}

	// send to blue player
	bytesSent = m_socketTcp->sendMsgToClient(m_blueSoldierSocket, msg.data(), msg.size(), NULL);
	if (bytesSent == SOCKET_ERROR) {
		errorMsg += "sendGameStateMsg msg to blue player failed with error: " + std::to_string(WSAGetLastError());
	}
}



std::vector<char> Server::recvMsgFromGreenPlayer()
{
	char* buffer = new char[64];
	int bytesReceived = 0;
	m_socketTcp->recvMsgFromClient(m_greenSoldierSocket, buffer, 64, bytesReceived);

	std::vector<char> msg;
	for (int i = 0; i < bytesReceived; i++) {
		msg.push_back(buffer[i]);
	}

	delete[](buffer);
	return msg;
}



std::vector<char> Server::recvMsgFromBluePlayer()
{
	char* buffer = new char[64];
	int bytesReceived = 0;
	m_socketTcp->recvMsgFromClient(m_blueSoldierSocket, buffer, 64, bytesReceived);

	std::vector<char> msg;
	for (int i = 0; i < bytesReceived; i++) {
		msg.push_back(buffer[i]);
	}

	delete[](buffer);
	return msg;
}
