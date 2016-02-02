#include "app1.h"

APP1_DATA app1Data;

void APP1_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app1Data.state = APP1_STATE_INIT;
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
    /* LED4 Output */
    SYS_PORTS_DirectionSelect(PORTS_ID_0, SYS_PORTS_DIRECTION_OUTPUT, PORT_CHANNEL_A, 0x8);
    uint32_t mask = 0x8;
    SYS_PORTS_Set(PORTS_ID_0, PORT_CHANNEL_A, mask, mask);
    /* GPIO Output for Logic Analyzer */
    SYS_PORTS_DirectionSelect(PORTS_ID_0, SYS_PORTS_DIRECTION_OUTPUT, PORT_CHANNEL_E, 0xFF);
    SYS_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_E, 0xFF);
    //SYS_PORTS_Set(PORTS_ID_0, PORT_CHANNEL_E, 0x2A, 0xFF);
}

void APP1_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( app1Data.state )
    {
        /* Application's initial state. */
        case APP1_STATE_INIT:
        {
            //Do whatever initialization tasks we need.
            app1Data.state = APP1_STATE_RUN;
            app1Data.letterRecvd = 'a';
            break;
        }

        /* TODO: implement your application state machine.*/
        case APP1_STATE_RUN:
        {
            //vBlinkTask();
            vCharRecvTask();
            app1Data.state = APP1_STATE_TX;
            break;
        }
        case APP1_STATE_TX:                                // USART transmit state
        {
            DRV_USART0_WriteByte(app1Data.letterRecvd);        // send modified byte received in APP_STATE_RX
            outputEvent(SendToUART);
            //app1Data.state = APP1_STATE_RX;                // change state to RX and wait for next received byte
            app1Data.state = APP1_STATE_RUN;
            break;
        }
        case APP1_STATE_RX:                                // USART receive state
        {
            if (!DRV_USART0_ReceiverBufferIsEmpty())       // if byte received in USART instance 0 (USART1 in this case)
            {
                app1Data.rx_byte = DRV_USART0_ReadByte();  // read received byte
                app1Data.tx_byte = app1Data.rx_byte + 1;   // modifying received byte confirms it was received
                app1Data.state = APP1_STATE_TX;            // change state to TX
            }
            break;
        }
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
 
void vBlinkTask()
{
    SYS_PORTS_Toggle(PORTS_ID_0, PORT_CHANNEL_A, 0x8);
}

void vCharRecvTask()
{
    /* Block on receiving a message from the queue by using 'portMAX_DELAY' */
    if( xQueueReceive( xQueue1, &(app1Data.letterRecvd), portMAX_DELAY ) != pdTRUE )
    {
        /* TODO: Debug... Notify via debugger that this event occurred */
        outputEvent(FailedToReceiveFromQueue);
    }
    else
    {
        outputEvent(ReceiveFromQueue);
    }
    
    /* Since UART is not set up yet, flash LED to show we made it past the block. */
    vBlinkTask();
}
/*******************************************************************************
 End of File
 */
