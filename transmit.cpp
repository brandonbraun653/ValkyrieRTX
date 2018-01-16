#include "transmit.hpp"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"

packetData txPacket;	/* Local copy of the transmitted packet */

int TXD  = (GPIO_NUM_10);
int RXD  = (GPIO_NUM_9);
int RTS  = (UART_PIN_NO_CHANGE);
int CTS  = (UART_PIN_NO_CHANGE);
int BUFF_SIZE = 256;
volatile esp_err_t error;

static const char* UART_TAG = "uart_special";
void transmitThread(void* parameter)
{
	uart_config_t uart_config;
	 
	uart_config.baud_rate = 115200;
	uart_config.data_bits = UART_DATA_8_BITS;
	uart_config.parity = UART_PARITY_DISABLE;
	uart_config.stop_bits = UART_STOP_BITS_1;
	uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
	
	//ESP_LOGI("uart1", "%s", "Starting up UART 1 for RTX.")
	//ESP_LOGI(UART_TAG, "%s(%d): %s", __FUNCTION__, __LINE__, "Starting up UART 1 for RTX.");
	error = uart_param_config(UART_NUM_1, &uart_config);
	error = uart_set_pin(UART_NUM_1, TXD, RXD, RTS, CTS);
	error = uart_driver_install(UART_NUM_1, BUFF_SIZE, BUFF_SIZE, 0, NULL, 0);
	
	size_t packetSize = sizeof(txPacket);
	
	TickType_t lastWakeTime = xTaskGetTickCount();
	
	for (;;)
	{
		/* Make sure to own a mutex to the output buffer for safe copying. Wait only a few ticks for it to become
		 * available before defaulting to using the last copied data. */
		if (xSemaphoreTake(outputBufferMutex, 5) == pdPASS)
		{
			txPacket = pktData;
			xSemaphoreGive(outputBufferMutex);
		}
		
		/* Transmit everything out in one burst (less than 54 bytes) */
		uart_write_bytes(UART_NUM_1, reinterpret_cast<char*>(&txPacket), packetSize);
		
		/* Force runtime frequency of nearly 50 Hz (20mS period) */
		vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(20));
		//vTaskDelay(pdMS_TO_TICKS(20));
	}
}