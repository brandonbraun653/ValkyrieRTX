#include "packet.hpp"

void packetThread(void* parameter)
{
	
	for (;;)
	{
		/* Block the task from executing until new data is available AND we can write to the output buffer */
		xSemaphoreTake(commandReady, portMAX_DELAY);
		xSemaphoreTake(outputBufferMutex, portMAX_DELAY);
		
		//Copy over to txbuffer
		txPkt = internalPkt;
		
		/* Release the mutex to allow the TX thread to use new data */
		xSemaphoreGive(outputBufferMutex);
	}
}