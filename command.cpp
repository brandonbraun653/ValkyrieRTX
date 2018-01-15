#include "command.hpp"


void commandThread(void* parameter)
{
	
	
	for (;;)
	{
		/* Block the task from executing until the semaphore has been given by another task */
		xSemaphoreTake(inputReady, portMAX_DELAY);
		
		
		//Do all the things here
		cmdResults.THROTTLE = inputData.THROTTLE;
		cmdResults.ROLL = inputData.ROLL;
		cmdResults.PITCH = inputData.PITCH;
		cmdResults.YAW = inputData.YAW;
		
		/* Inform the packetization thread that it should now execute */
		xSemaphoreGive(commandReady);
	}
}