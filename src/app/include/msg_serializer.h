#pragma once 
#include <string.h>
#include <msg_gps_buffer.h>
#include <assert.h>

void serialize(msg_number_t msg_number, void* msg, void* dest)
{
    assert(msg != NULL);
    assert(dest != NULL);

    switch (msg_number)
    {
        case MSG_GPS_BUFFER_FWD: 
        {
            msg_gps_buffer_fwd* msg = (msg_gps_buffer_fwd*)msg;
            memcpy(dest, &msg->buff_part, sizeof(msg->buff_part));
        }
    }
}