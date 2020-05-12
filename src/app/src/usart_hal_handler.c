#include <hal/usart.h>
#include <libopencm3/stm32/usart.h>
#include <gps.h>
#include <ec_bus.h>
#include <msg_gps_buffer.h>

// TODO: All of this staff below, can be moved into isr.c -> to consider! :) 

//extern 
extern gps_t gps;

static void __handle_usart_1();

void hal_usart_isr(uint32_t usart)
{
    if (usart == USART1) {
        __handle_usart_1();
    }
}

void __handle_usart_1()
{
  if (usart_get_flag(USART1, USART_FLAG_RXNE))
  {
    uint8_t data = usart_recv(USART1) & 0x00ff;
    gps_receive_char(&gps, data);

    if (1 == 1) // send through usb 
    {
      msg_gps_buffer_fwd msg = {
        .buff_part = data
      };

      ec_bus_send_msg(MSG_GPS_BUFFER_FWD, &msg);
    }
  }
}

// PRIVATE FUNCTIONS IMPLEMENTATION //