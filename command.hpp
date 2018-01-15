#pragma once
#ifndef COMMAND_HPP_
#define COMMAND_HPP_ 

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "messaging.hpp"

extern void commandThread(void* parameter);

#endif /* COMMAND_HPP_ */