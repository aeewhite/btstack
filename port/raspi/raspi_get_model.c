
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "raspi_get_model.h"

/**
 * Raspberry Pi model detection based on,
 * https://elinux.org/RPi_HardwareHistory
**/
int raspi_get_model()
{
    FILE *f = fopen( "/proc/cpuinfo", "rb" );
    if( f == NULL )
    {
        perror( "can't open cpuinfo!" );
        return MODEL_UNKNOWN;
    }

    int ret = 0;
    uint32_t revision = 0;
    uint32_t model = MODEL_UNKNOWN;
    char line[100] = { 0 };
    char *ptr = NULL;
    for(; ret < 1;)
    {
        ptr = fgets( line, 100, f );
        if( ptr == NULL )
            break;
        ret = sscanf( line, "Revision : %x\n", &revision );
    }
    
    fclose( f );
    
    switch( revision )
    {
    case 0x9000c1:
        model = MODEL_ZERO_W;
        break;
    case 0xa02082:
    case 0xa22082:
    case 0xa32082:
        model = MODEL_3B;
        break;
    case 0xa020d3:
        model = MODEL_3BPLUS;
        break;
    case 0x9020e0:
        model = MODEL_3APLUS;
        break;
    case 0xa03111:
    case 0xb03111:
    case 0xb03112:
    case 0xb03114:
    case 0xb03115:
    case 0xc03111:
    case 0xc03112:
    case 0xc03114:
    case 0xc03115:
    case 0xd03114:
    case 0xd03115:
        model = MODEL_4B;
        break;
    default:
        break;
    }
    
    return model;
}


