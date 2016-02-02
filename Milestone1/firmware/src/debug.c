#include "debug.h"

void outputEvent( uint32_t value  )
{
    //uint32_t mask = 0x00FF;
    SYS_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_E, 0xFF);
    SYS_PORTS_Set( PORTS_ID_0, PORT_CHANNEL_E, value, 0xFF );
}
