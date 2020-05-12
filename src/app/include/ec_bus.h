#pragma once 

//External control - used to forward gps data torwards pc and receive configuration

#include <stdint.h>

typedef uint8_t msg_number_t;

typedef void (msg_handler_t)(void);
typedef void (on_connected_handler_t)(void);
typedef void (on_disconnected_handler_t)(void);

void ec_bus_init();
void ec_bus_register_on_connected_handler(on_connected_handler_t* const handler);
void ec_bus_register_on_disconnected_handler(on_disconnected_handler_t* const handler);
void ec_bus_register_msg_handler(msg_number_t msg_number, msg_handler_t* const handler);
void ec_bus_send_msg(msg_number_t msg_number, void* const msg);
void ec_bus_task();