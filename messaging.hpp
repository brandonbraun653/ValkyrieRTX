#pragma once
#ifndef MESSAGING_HPP_
#define MESSAGING_HPP_

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "rtx.hpp"

/* Semaphores */
extern SemaphoreHandle_t inputReady;
extern SemaphoreHandle_t commandReady;

/* Mutexes */
extern SemaphoreHandle_t outputBufferMutex;

/* Buffers for passing data between tasks */
extern inputReadings inputData;
extern parseResults cmdResults;
extern packetData pktData;

#endif /* MESSAGING_HPP_ */