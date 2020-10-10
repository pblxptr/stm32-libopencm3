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
  void usart1_isr()
  {
    using namespace platform::ll_drivers::uart;

    auto* uart = &uart1;

    //TODO: Enhance flag clearing

    [[maybe_unused]] auto cr = USART1_SR;
    [[maybe_unused]] auto dr = USART1_DR;

    if (uart->fwd_isr != nullptr)
    {
      uart->fwd_isr(uart->fwd_isr_ctx);
    }
  }
}
