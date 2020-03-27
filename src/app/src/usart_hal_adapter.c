#include <hal/usart.h>
#include <libopencm3/stm32/usart.h>
#include <gps.h>

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
    uint16_t data = usart_recv(USART1);
    
    gps_receive_char(&gps, data & 0x00ff);
  }
}

// PRIVATE FUNCTIONS IMPLEMENTATION //