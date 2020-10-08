#include<platform/hal/uart.hpp>
 
extern "C" {
  #include <libopencm3/stm32/usart.h>
}

using namespace drivers::uart;

namespace platform::ll_drivers::uart
{
  STM32UartDriver uart1;
}

extern "C" {
  __attribute__((naked)) void usart1_isr()
  {
    using namespace platform::ll_drivers::uart;

    auto* uart = &uart1;

    if (uart->fwd_isr != nullptr)
    {
      uart->fwd_isr(uart->fwd_isr_ctx);
    }

    //TODO: Clean after interrutp 
  }
}
