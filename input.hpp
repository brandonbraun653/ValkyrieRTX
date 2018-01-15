#pragma once
#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "messaging.hpp"

void inputThread(void* parameter);

#endif /* INPUT_HPP */