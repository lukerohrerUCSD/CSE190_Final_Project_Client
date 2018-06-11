#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <bitset>

class ClientGame
{
public:

	struct clientInfo {
		glm::mat4 headToWorld;
		glm::mat4 handToWorld;
	};

	ClientGame(void);
	~ClientGame(void);

	clientInfo clientState;

	ClientNetwork* network;

	void sendActionPackets();
	void sendPacketToServer();
	void handlePacketFromServer();
	void updateClientInfo(glm::mat4 headMtx, glm::mat4 handMtx);
	void createPacket(char data[]);
	void copyMatrixToData(glm::mat4 matrix, char data[], int startingIndex);

    char network_data[MAX_PACKET_SIZE];

    void update();
};

