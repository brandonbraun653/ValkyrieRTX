#include "messaging.hpp"

/* Semaphores */
SemaphoreHandle_t inputReady = xSemaphoreCreateBinary();
SemaphoreHandle_t commandReady = xSemaphoreCreateBinary();

/* Mutexes */
SemaphoreHandle_t outputBufferMutex = xSemaphoreCreateMutex();

/* Buffers */
packetData txPkt;
packetData internalPkt;