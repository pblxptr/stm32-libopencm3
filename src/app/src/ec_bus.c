#include <ec_bus.h>
#include <ec_bus_transport.h>
#include <target.h>
#include <led.h>
#include <delay.h>
#include <msg_serializer.h>
#include <list.h>

static msg_number_t* handlers[10];
static uint8_t receive_data_buffer[64];
static uint8_t send_data_buffer[64];


// PRIVATE FUNCTION DECLARATIONS //
void __received_callback();
void __sent_callback();

void ec_bus_init()
{
    ec_bus_transport_init_t bus_transport_init = {
        .receive_buffer = receive_data_buffer,
        .receive_buffer_len = sizeof(receive_data_buffer),
        .received_callback = &__received_callback,

        .send_buffer = send_data_buffer,
        .send_buffer_len = sizeof(send_data_buffer),
        .sent_callback = &__sent_callback,
    }; 

    ec_bus_transport_init(&bus_transport_init);
}

void ec_bus_register_on_connected_handler(on_connected_handler_t* const handler)
{

}

void ec_bus_register_on_disconnected_handler(on_disconnected_handler_t* const handler)
{

}

void ec_bus_register_msg_handler(msg_number_t msg_number, msg_handler_t* const handler)
{

    // handlers[msg_number] = handler;
}

void ec_bus_send_msg(msg_number_t msg_number, void* const msg)
{
    char x = 'A';

    for (size_t i = 0; i < sizeof(send_data_buffer); i++)
    {
        send_data_buffer[i] = x;
        x = (++x) % 26; 
    }

    send_data_buffer[63] = '\r';

    //Send 
    ec_bus_transport_send();
}

void ec_bus_task()
{
    ec_bus_transport_poll();
}

extern led_t status_led;

void blink(uint8_t times)
{
    for (size_t i = 0; i < times; i++)
    {
        delay_ms(1000);
        led_set_state(&status_led, LED_STATE_ON);
        delay_ms(1000);
        led_set_state(&status_led, LED_STATE_OFF);
    }
}

// PRIVATE FUNCTION IMPLEMENTATIONS //
void __received_callback()
{
    uint8_t msg_number = receive_data_buffer[0];
    
    switch (msg_number) 
    {
        case 1:
            blink(1);
        break;

        case 2:
            blink(2);
        break;

        case 3: 
            blink(3);
        break;

        default:
            blink(0);
    }
}

void __sent_callback()
{
    
}
