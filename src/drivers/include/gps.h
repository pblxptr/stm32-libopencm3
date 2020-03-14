#pragma once

#include <ring_buffer.h>
#include <libopencm3/stm32/usart.h>

#define GPS_BUFFER_SIZE         256
#define GPS_WORKING_BUFFER_SIZE 128

static uint8_t GPS_WORKING_BUFFER_DATA[GPS_WORKING_BUFFER_SIZE];
static rbuff_t gps_rbuff;

void gps_init(uint32_t usart)
{
    //init usart   
}

void gpis_receive_char()
{
    
}