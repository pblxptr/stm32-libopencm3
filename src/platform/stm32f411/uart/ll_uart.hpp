#pragma once

#include <ll_dma.hpp>

extern "C" {
  #include <libopencm3/stm32/usart.h>
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/cm3/nvic.h>
  #include <libopencm3/stm32/dma.h>
  #include <libopencm3/stm32/rcc.h>
}

namespace {
  using namespace platform::ll_drivers::dma;
}

namespace platform::ll_drivers::uart
{
  using uart_flags_t = uint32_t;
  using uart_irq_t = void(*)(void*, uart_flags_t);

  struct STM32UartDriver : drivers::uart::UartDriver
  {
    platform::ll_drivers::dma::DmaStream* rx_dma;
    platform::ll_drivers::dma::DmaStream* tx_dma;
    uart_irq_t fwd_isr;
    void* fwd_isr_ctx;

    STM32UartDriver() //TODO: Add id to contructor
      : rx_dma{nullptr}
      , tx_dma{nullptr}
      , fwd_isr{nullptr}
      , fwd_isr_ctx{nullptr} {}
  };

  extern STM32UartDriver uart1;
  extern STM32UartDriver uart2;

  //API
  template<uint32_t UART_ID>
  constexpr STM32UartDriver* get_driver();

  template<uint32_t UART_ID>
  inline void enable_driver(STM32UartDriver*);

  //SPECIALIZATIONS 
  template<> constexpr STM32UartDriver* get_driver<USART1>() { return &uart1; }
  template<> constexpr STM32UartDriver* get_driver<USART2>() { return &uart2; }

  template<> inline void enable_driver<USART1>(STM32UartDriver* driver)
  {
    nvic_enable_irq(NVIC_USART1_IRQ);
    nvic_enable_irq(NVIC_DMA2_STREAM2_IRQ);
    nvic_enable_irq(NVIC_DMA2_STREAM7_IRQ);

    driver->rx_dma = &platform::ll_drivers::dma::dma2_stream2;
    driver->tx_dma = &platform::ll_drivers::dma::dma2_stream7;
  }

  template<> inline void enable_driver<USART2>(STM32UartDriver* driver)
  {
    nvic_enable_irq(NVIC_USART2_IRQ);
    nvic_enable_irq(NVIC_DMA1_STREAM5_IRQ);
    nvic_enable_irq(NVIC_DMA1_STREAM6_IRQ);

    driver->rx_dma = &platform::ll_drivers::dma::dma1_stream5;
    driver->tx_dma = &platform::ll_drivers::dma::dma1_stream6;
  }
}