#include<platform/hal/uart.hpp>
 
extern "C" {
  #include <libopencm3/stm32/usart.h>
}

using namespace drivers::uart;

namespace {
  static inline void uart_clear_idle_flag(uint32_t uart_id)
  {
    [[maybe_unused]] auto sr = USART_SR(uart_id);
    [[maybe_unused]] auto dr = USART_DR(uart_id);
  }

  static inline void uart_clear_rxne_flag(uint32_t uart_id)
  {
    [[maybe_unused]] auto sr = USART_SR(uart_id);
    [[maybe_unused]] auto dr = USART_DR(uart_id);
  }
}

namespace platform::ll_drivers::uart
{
  STM32UartDriver uart1;
}

extern "C" {
  void usart1_isr()
  {
    using namespace platform::ll_drivers::uart;

    auto* uart = &uart1;
    uart_flags_t flags{0};

    //When idle interrupt is triggered
    if ((USART_CR1(uart->uart_id) & USART_CR1_IDLEIE) && 
        (USART_SR(uart->uart_id) & USART_FLAG_IDLE) 
       )
    {
      flags |= USART_FLAG_IDLE;
      uart_clear_idle_flag(uart->uart_id);
    }

    //When character received interrupt is triggered
    else if ((USART_CR1(uart->uart_id) & USART_CR1_RXNEIE) && 
            (USART_SR(uart->uart_id) & USART_FLAG_RXNE) 
            )
    {
      flags |= USART_FLAG_RXNE;
      uart_clear_rxne_flag(uart->uart_id);
    }

    //Call isr handler
    if (uart->fwd_isr != nullptr)
    {
      uart->fwd_isr(uart->fwd_isr_ctx, flags);
    }

  }
}
