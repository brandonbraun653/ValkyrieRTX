#include "input.hpp"

#include "driver/gpio.h"
#include "driver/adc.h"

/* Notes on ADC Input:
 *	The voltage variations here are bound between 0.0V and 3.3V, however the actual inputs 
 *	from the various switches and knobs do not display that full scale range nor do they all
 *	share the same range. Unfortunately, their min's and max's all vary quite a bit. 
 *	
 * Connections:
 *	GPIO36/ADC1_0 -> Switch Right 
 *	GPIO39/ADC1_3 -> Switch Left 
 *	GPIO34/ADC1_6 -> Throttle 
 *	GPIO35/ADC1_7 -> Roll
 *	GPIO32/ADC1_4 -> Pitch
 *	GPIO33/ADC1_5 -> Yaw 
 * */

const float VDDA = 3.30;
const float RES = 4095.0;

const adc1_channel_t SWR = ADC1_CHANNEL_0;
const adc1_channel_t SWL = ADC1_CHANNEL_3;
const adc1_channel_t THROTTLE = ADC1_CHANNEL_6;
const adc1_channel_t ROLL = ADC1_CHANNEL_7;
const adc1_channel_t PITCH = ADC1_CHANNEL_4;
const adc1_channel_t YAW = ADC1_CHANNEL_5;

const gpio_num_t sigPin = GPIO_NUM_23;

void inputThread(void* parameter)
{
	/* Setup the bit width */
	adc1_config_width(ADC_WIDTH_12Bit);
	
	/* Configure each channel to use full scale resolution defined by VDDA */
	adc1_config_channel_atten(SWR, ADC_ATTEN_11db);
	adc1_config_channel_atten(SWL, ADC_ATTEN_11db);
	adc1_config_channel_atten(THROTTLE, ADC_ATTEN_11db);
	adc1_config_channel_atten(ROLL, ADC_ATTEN_11db);
	adc1_config_channel_atten(PITCH, ADC_ATTEN_11db);
	adc1_config_channel_atten(YAW, ADC_ATTEN_11db);
	
	
	#ifdef DEBUG
	gpio_pad_select_gpio(sigPin);
	gpio_set_direction(sigPin, GPIO_MODE_OUTPUT);
	gpio_set_level(sigPin, 0);
	#endif
	
	TickType_t lastWakeTime = xTaskGetTickCount();
	for (;;)
	{
		/* Grab all the readings, convert, and place them into the output buffer */
		inputData.SWR		= VDDA * (adc1_get_voltage(SWR) / RES);
		inputData.SWL		= VDDA * (adc1_get_voltage(SWL) / RES);
		inputData.THROTTLE	= VDDA * (adc1_get_voltage(THROTTLE) / RES);
		inputData.ROLL		= VDDA * (adc1_get_voltage(ROLL) / RES);
		inputData.PITCH		= VDDA * (adc1_get_voltage(PITCH) / RES);
		inputData.YAW		= VDDA * (adc1_get_voltage(YAW) / RES);
		
		#ifdef DEBUG
		gpio_set_level(sigPin, 0);
		gpio_set_level(sigPin, 1);
		gpio_set_level(sigPin, 0);
		#endif
		
		/* Now that the task has completed, inform the input data parser that it can run now */
		xSemaphoreGive(inputReady);
		
		/* Force runtime frequency of nearly 100 Hz (10mS period) */
		vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(10));
		//vTaskDelay(pdMS_TO_TICKS(10));
	}
}
