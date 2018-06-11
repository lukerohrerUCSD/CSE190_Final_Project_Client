#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class ClientGame
{
public:
	ClientGame(void);
	~ClientGame(void);

	ClientNetwork* network;

	void sendActionPackets();
	void sendPacketToServer();
	void handlePacketFromServer();
	void createPacket(char data[]);

    char network_data[MAX_PACKET_SIZE];

    void update();
};

