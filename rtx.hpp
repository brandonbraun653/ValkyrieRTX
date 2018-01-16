#pragma once
#ifndef RTX_HPP_
#define RTX_HPP_


#include <stdint.h>

struct inputReadings
{
	float SWR = 0.0;
	float SWL = 0.0;
	float THROTTLE = 0.0;
	float ROLL = 0.0;
	float PITCH = 0.0;
	float YAW = 0.0;
};

struct parseResults
{
	
	float THROTTLE = 0.0;
	float ROLL = 0.0;
	float PITCH = 0.0;
	float YAW = 0.0;
};

struct packetData
{
	float THROTTLE = 0.0;
	float ROLL = 0.0;
	float PITCH = 0.0;
	float YAW = 0.0;
};
#endif