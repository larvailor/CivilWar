#pragma once

#pragma warning(disable: 4996)

#include "Config.h"

#include "BaseCWException.h"

#include <WinSock2.h>
#include <list>

class Network
{
public:
	Network();
	~Network();

	void connectToCWServer();

private:
	// variables
	/*Soldier* m_player;
	Soldier* m_enemy;

	std::list<Bullet> m_playerBullets;
	std::list<Bullet> m_enemyBullets;*/

	SOCKET m_listenClientSocket;
	//SOCKADDR_IN m_clientAddr;
	//int m_clientAddrSize;

	SOCKADDR_IN m_serverAddr;
	int m_serverAddrSize;

	// methods
	void initializeWinSock();
	void createSocket();
	void initializeSockAddr();
	void bindSocket();
};
