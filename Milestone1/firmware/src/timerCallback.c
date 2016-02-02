#include "app1_public.h"

const char teamNames[59] = "KYLE IMHOF RACHAEL STEMPFLEY ALEX VAN BRUNT ANDREW SANDERS ";
short sLtrCount = 0;

void vTimerCallback( TimerHandle_t pxTimer )
{
    /* This is exactly why void pointers are B.S.!!! I forgot the '&' in the cast and it crashed the entire RTOS!!!! */
    if( xQueueSend( xQueue1, (void *)&teamNames[sLtrCount], (TickType_t)10 ) != pdPASS )
    {
        /* TODO: Debug... Failed to post the message, even after 10 ticks. 
         Handle return value */
        outputEvent(QueueFull);
    }
    else
    {
        outputEvent(SendToQueue);
    }
    sLtrCount++;
    if(sLtrCount > 58) //TODO: Include std header and make this use strlen()-1
    {
        sLtrCount = 0;
    }
}