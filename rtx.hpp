#pragma once
#ifndef RTX_HPP_
#define RTX_HPP_


#include <stdint.h>

/* Rather than use an enum, this typedef approach is used to 
 * force a strict size because this will be eventually transmitted
 * over a bandwidth limited Wireless connection with XBEE */
typedef uint8_t packetTypes;
static const packetTypes PACKET_COMMAND		= 1;
static const packetTypes PACKET_CONTROLS	= 2;
static const packetTypes PACKET_REQUEST		= 4;

#pragma pack(push,1)
struct packetData
{
	packetTypes pktType = PACKET_CONTROLS;
	float SWR = 0.0;
	float SWL = 0.0;
	float THROTTLE = 0.0;
	float ROLL = 0.0;
	float PITCH = 0.0;
	float YAW = 0.0;
	//Eventually add CRC calculations 
};
#pragma pack(pop)
#endif