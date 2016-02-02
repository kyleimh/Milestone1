#ifndef _APP1_PUBLIC_H    /* Guard against multiple inclusion */
#define _APP1_PUBLIC_H

#include "FreeRTOS.h" /* Necessary to include before including "timers.h" */
#include "timers.h"
#include "queue.h"
#include "debug.h"

TimerHandle_t xTimer1;
QueueHandle_t xQueue1;

short sLtrCount;

void vTimerCallback( TimerHandle_t pxTimer );

#endif /* _APP1_PUBLIC_H */
