#pragma once 
#include <stdint.h>
#include <messages.h>

inline uint8_t msg_deserialize_header(uint8_t* buffer)
{
    return buffer[0]; 
}

void msg_serialize_header(uint8_t* buffer, uint8_t msg_number);