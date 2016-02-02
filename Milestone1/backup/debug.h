/* 
 * File:   debug.h
 * Author: Kyle
 *
 * Created on February 2, 2016, 1:34 PM
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include "FreeRTOS.h"
#include "system_config/default/system_definitions.h"

/* Success debug codes */
#define SendToQueue 1
#define ReceiveFromQueue 2
#define SendToUART 3

/* Error debug codes */
#define FailedToReceiveFromQueue 4
#define QueueFull 5
#define TimerNotCreated 6
#define TimerNotActive 7
#define QueueNotCreated 8

void outputEvent( uint32_t value  );

#endif	/* DEBUG_H */

