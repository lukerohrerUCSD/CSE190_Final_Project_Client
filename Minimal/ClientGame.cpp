#include "StdAfx.h"
#include "ClientGame.h"
#include <bitset>
#include <iostream>

ClientGame::ClientGame(void)
{

    network = new ClientNetwork();

    // send init packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = INIT_CONNECTION;

    packet.serialize(packet_data);

    NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

ClientGame::~ClientGame(void)
{
}

void ClientGame::sendActionPackets()
{
    // send action packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = ACTION_EVENT;

	//createPacket(packet.data);

    packet.serialize(packet_data);

    NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::sendPacketToServer()
{
	// send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ClientToServer;

	//createPacket(packet.data);
	packet.headMtx = clientState.headToWorld;
	packet.handMtx = clientState.handToWorld;
	packet.flag = clientState.flag;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::setClientState(float flag) {
	clientState.flag = flag;
}


void ClientGame::handlePacketFromServer(Packet packet) 
{
	serverState.handToWorld = packet.handMtx;
	serverState.headToWorld = packet.headMtx;

	for (int i = 0; i < 32; i++) {
		serverState.lines[i] = packet.lines[i];
	}

	serverState.lineSpawn = packet.lineSpawn;
	serverState.gameOver = packet.gameOver;
}

ClientGame::stateInfo ClientGame::getServerState() {
	return serverState;
}

void floatToBytes(char* bytes_temp, float f) {
	union {
		float f;
		unsigned char bytes[4];
	} floatAndChar;

	floatAndChar.f = f;
	memcpy(bytes_temp, floatAndChar.bytes, 4);
}

void ClientGame::copyMatrixToData(glm::mat4 matrix, char data[], int startingIndex) {

	int index = startingIndex;

	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {

			float value = matrix[j][k];

			//std::cout << value;

			char bytes_temp[4];
			floatToBytes(&bytes_temp[0], value);
			for (int l = 0; l < 4; l++) {
				data[index] = bytes_temp[l];

				//std::bitset<8> x(data[index]);
				//std::cout << x;

				index++;
			}
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;
}

void ClientGame::updateClientInfo(glm::mat4 headMtx, glm::mat4 handMtx)
{
	clientState.headToWorld = headMtx;
	clientState.handToWorld = handMtx;
}

void ClientGame::createPacket(char data[])
{
	glm::mat4 headMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
	//glm::mat4 headMatrix = clientState.headToWorld;

	//copyMatrixToData(headMatrix, data, 0);


}

void ClientGame::update()
{
    Packet packet;
    int data_length = network->receivePackets(network_data);

    if (data_length <= 0) 
    {
        //no data recieved
        return;
    }

    int i = 0;
    while (i < (unsigned int)data_length) 
    {
        packet.deserialize(&(network_data[i]));
        i += sizeof(Packet);

        switch (packet.packet_type) {

            case ACTION_EVENT:

                //printf("client received action event packet from server\n");

                //sendActionPackets();
				//sendPacketToServer();

                break;

			case ServerToClient:

				handlePacketFromServer(packet);
				serverState.headToWorld = packet.headMtx;
				serverState.handToWorld = packet.handMtx;


				sendPacketToServer();

				break;

            default:

                //printf("error in packet types\n");

                break;
        }
    }
}
