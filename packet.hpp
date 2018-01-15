#pragma once
#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "messaging.hpp"

extern void packetThread(void* parameter);

#endif /* PACKET_HPP_ */