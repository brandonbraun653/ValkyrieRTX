#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* ValkyrieRTX Includes */
#include "input.hpp"
#include "command.hpp"
#include "packet.hpp"
#include "transmit.hpp"

#define BLINK_GPIO GPIO_NUM_2
void statusLed(void* parameter);

#ifdef __cplusplus
extern "C" 
#endif
void app_main()
{
	nvs_flash_init();
	
	xTaskCreate(inputThread, "input", 1000, NULL, 3, NULL);
	xTaskCreate(transmitThread, "tx", 1000, NULL, 3, NULL);
	xTaskCreate(commandThread, "cmd", 1000, NULL, 2, NULL);
	xTaskCreate(packetThread, "pkt", 1000, NULL, 2, NULL);
	xTaskCreate(statusLed, "led", 512, NULL, 2, NULL);
	
	//Note: No need to start the scheduler as it was already done in the CPU core init
	//		function provided with the ESP32 firmware.
}


void statusLed(void* parameter)
{
	gpio_pad_select_gpio(BLINK_GPIO);
	gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
	
	TickType_t lastWakeTime = xTaskGetTickCount();
	for (;;)
	{
		
		gpio_set_level(BLINK_GPIO, 1);
		vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(100));
		//vTaskDelay(pdMS_TO_TICKS(100));
		
		gpio_set_level(BLINK_GPIO, 0);
		vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(1000));
		//vTaskDelay(pdMS_TO_TICKS(1000));
	}
}