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

	struct stateInfo {
		glm::mat4 headToWorld;
		glm::mat4 handToWorld;
	};

	ClientGame(void);
	~ClientGame(void);

	stateInfo clientState;
	stateInfo serverState;

	ClientNetwork* network;

	void sendActionPackets();
	void sendPacketToServer();
	void handlePacketFromServer(Packet packet);
	void updateClientInfo(glm::mat4 headMtx, glm::mat4 handMtx);
	void createPacket(char data[]);
	void copyMatrixToData(glm::mat4 matrix, char data[], int startingIndex);
	stateInfo getServerState();

    char network_data[MAX_PACKET_SIZE];

    void update();
};

