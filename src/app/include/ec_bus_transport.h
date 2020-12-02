#pragma once 

#include <stdint.h>
#include <stddef.h>

typedef void(received_callback_t)(void);
typedef void(sent_callback_t)(void);

typedef struct _ec_bus_transport_init_t_ {
    uint8_t* receive_buffer;
    size_t receive_buffer_len;
    received_callback_t* received_callback;
    uint8_t* send_buffer;
    size_t send_buffer_len;
    sent_callback_t* sent_callback;
} ec_bus_transport_init_t;

void ec_bus_transport_init(const ec_bus_transport_init_t* init_config);
void ec_bus_transport_send();
void ec_bus_transport_poll();