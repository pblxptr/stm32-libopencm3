extern "C" {
  #include <libopencm3/stm32/usart.h>
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/stm32/rcc.h>
}

#include <uprintf.hpp>

namespace utils::debug
{
  void uprintf_init(uint32_t usart)
  {
    //RCC 
    rcc_periph_clock_enable(RCC_USART1);

    //GPIO
    gpio_set_mode(GPIO_BANK_USART1_TX, GPIO_MODE_OUTPUT_50_MHZ, 
      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);
    
    gpio_set_mode(GPIO_BANK_USART1_RX, GPIO_MODE_INPUT, 
      GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, GPIO_USART1_RX);

    //USART
    usart_set_mode(USART1, USART_MODE_TX_RX);
    usart_set_baudrate(USART1, 9600);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, 1);
    usart_enable(USART1);

  }
  void uprintf_send(uint32_t usart, const char* data)
  {
    while (*data)
    {
      usart_send_blocking(USART1, *data++);
    }
  }

  void uprintf_send(uint32_t usart, const uint8_t data)
  {
    usart_send_blocking(USART1, data);
  }
}