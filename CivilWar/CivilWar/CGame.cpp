#include "CGame.h"

#include <vector>

CGame::CGame() :
	m_isRunning(false)
{
	m_network = new Network();
	m_serializer = new CSerializer();
}



CGame::~CGame()
{
	delete(m_serializer);
	delete(m_network);
}



void CGame::initAll()
{
	
}



void CGame::connectToCWServer(const char* ip, int port)
{
	m_network->connectToCWServer(ip, port);
}



void CGame::start()
{
	m_isRunning = true;
}



void CGame::recvDataAndUpdate()
{
	std::vector<char> battlefieldMsg = m_network->recvMsg();
	m_serializer->translateMsg(battlefieldMsg);

	std::vector<char> greenSoldierMsg = m_network->recvMsg();
	m_serializer->translateMsg(greenSoldierMsg);

	std::vector<char> blueSoldierMsg = m_network->recvMsg();
	m_serializer->translateMsg(blueSoldierMsg);
}
