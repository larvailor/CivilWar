#pragma once

#include "Network.h"
#include "CSerializer.h"


class CGame
{
public:
	CGame();
	~CGame();

	void initAll();
	void connectToCWServer(const char* ip, int port);
	void start();
	bool isRunning() const { return m_isRunning; }

	void recvDataAndUpdate();

private:
	// variables
	Network* m_network;
	CSerializer* m_serializer;

	bool m_isRunning;
};
