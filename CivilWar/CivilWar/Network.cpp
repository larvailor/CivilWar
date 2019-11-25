#include "BaseCWException.h"

#include "Network.h"

Network::Network() :
	m_socketTcp(nullptr)
{

}



Network::~Network()
{
	delete(m_socketTcp);
}



void Network::connectToCWServer(const char* ip, int port)
{
	initializeWinSock();
	createSockets();
	try {
		m_socketTcp->connectToCwServer(ip, port);
	}
	catch (BaseCWException e) {
		WSACleanup();
		throw e;
	}
}



void Network::initializeWinSock()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int iResult = WSAStartup(wVersionRequested, &wsaData);
	if (iResult != 0) {
		std::string errorMsg = "Network.initializeWinSock failed with error: " + std::to_string(WSAGetLastError());
		throw BaseCWException(errorMsg);
	}
}



void Network::createSockets()
{
	// create TCP socket
	try {
		m_socketTcp = new CwClientSocketTcp();
	}
	catch (BaseCWException e) {
		WSACleanup();
		throw e;
	}
}



std::vector<char> Network::recvMsg()
{
	char* buffer = new char[2048];
	int bytesReceived = 0;
	m_socketTcp->recvMsgFromServer(buffer, 2048, bytesReceived);
	
	std::vector<char> msg;
	for (int i = 0; i < bytesReceived; i++) {
		msg.push_back(buffer[i]);
	}

	delete[](buffer);
	return msg;
}



void Network::sendMoveMsg(CMoveMsg* moveMsg)
{
	std::vector<char> msg = moveMsg->getMsg();
	delete(moveMsg);

	int bytesSent = 0;
	std::string errorMsg;
	bytesSent = m_socketTcp->sendMsgToServer(msg.data(), msg.size(), NULL);
}



void Network::sendMoveAndFireMsg(CMoveAndFireMsg* moveAndFireMsg)
{
	std::vector<char> msg = moveAndFireMsg->getMsg();
	delete(moveAndFireMsg);

	int bytesSent = 0;
	std::string errorMsg;
	bytesSent = m_socketTcp->sendMsgToServer(msg.data(), msg.size(), NULL);
}
