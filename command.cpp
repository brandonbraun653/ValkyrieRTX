#include "command.hpp"
#include "rtx.hpp"


void commandThread(void* parameter)
{
	
	
	for (;;)
	{
		/* Block the task from executing until the semaphore has been given by another task */
		xSemaphoreTake(inputReady, portMAX_DELAY);
		
		
		//have one type that you just pass around and add more data to 
		internalPkt.pktType = PACKET_CONTROLS;
		
		/* Inform the packetization thread that it should now execute */
		xSemaphoreGive(commandReady);
	}
}