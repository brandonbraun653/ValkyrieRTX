#pragma once
#ifndef MESSAGING_HPP_
#define MESSAGING_HPP_

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

/* Semaphores */
extern SemaphoreHandle_t inputReady;
extern SemaphoreHandle_t commandReady;

/* Mutexes */
extern SemaphoreHandle_t outputBufferMutex;

/* Buffers for passing data between tasks */
struct inputReadings
{
	float SWR = 0.0;
	float SWL = 0.0;
	float THROTTLE = 0.0;
	float ROLL = 0.0;
	float PITCH = 0.0;
	float YAW = 0.0;
};
extern inputReadings inputData;

struct parseResults
{
	
	float THROTTLE = 0.0;
	float ROLL = 0.0;
	float PITCH = 0.0;
	float YAW = 0.0;
};
extern parseResults cmdResults;

struct packetData
{
	float THROTTLE = 0.0;
	float ROLL = 0.0;
	float PITCH = 0.0;
	float YAW = 0.0;
};
extern packetData pktData;

#endif /* MESSAGING_HPP_ */