#pragma once
#ifndef TRANSMIT_HPP_
#define TRANSMIT_HPP_

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "messaging.hpp"

extern void transmitThread(void* parameter);

#endif /* TRANSMIT_HPP_ */