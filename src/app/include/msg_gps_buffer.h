#pragma once 

#include <stdint.h>

#define MSG_GPS_BUFFER_FWD (1)

typedef struct _msg_gps_buffer_fwd_
{
    uint8_t buff_part;
} msg_gps_buffer_fwd;