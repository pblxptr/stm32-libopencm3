#pragma once 

//External control - used to forward gps data torwards pc and receive configuration

#include <stdint.h>

typedef void (msg_handler)(void);

void ec_bus_init();
void ec_bus_register_msg_handler(uint32_t msg_number, const msg_handler* handler);
void ec_bus_task();