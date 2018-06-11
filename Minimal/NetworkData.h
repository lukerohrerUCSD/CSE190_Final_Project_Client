#pragma once
#include <string.h>
#include <glm/glm.hpp>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {

    INIT_CONNECTION = 0,

    ACTION_EVENT = 1,

	ClientToServer = 2,

	ServerToClient = 3,

};

struct Packet {

    unsigned int packet_type;
	//char data[256];
	glm::mat4 headMtx;
	glm::mat4 handMtx;

    void serialize(char * data) {
        memcpy(data, this, sizeof(Packet));
    }

    void deserialize(char * data) {
        memcpy(this, data, sizeof(Packet));
    }
};