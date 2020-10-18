#pragma once

#include <ll_uart_if.hpp>
#include <ll_dma_if.hpp>

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
  extern STM32UartDriver uart1;
  extern STM32UartDriver uart2;

  //USART1
  template<>
  inline void configure_uart_gpio<USART1>()
  {
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);
	  gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);
  }

  template<>
  inline void configure_uart_gpio<USART2>()
  {
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
	  gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);
  }

  template<>
  inline void configure_interrupts<USART1>()
  {
    nvic_enable_irq(NVIC_USART1_IRQ);
  }

  template<>
  inline void configure_interrupts<USART2>()
  {
    nvic_enable_irq(NVIC_USART2_IRQ);
  }

  template<>
  inline void attach_dma<USART1>(STM32UartDriver* driver)
  {
    //Enable peripheral clock
    rcc_periph_clock_enable(RCC_DMA2);

    //Enable nvic interrupt for dma stream
    nvic_enable_irq(NVIC_DMA2_STREAM2_IRQ);
    nvic_enable_irq(NVIC_DMA2_STREAM7_IRQ);
    
    //Assing dma channel handler
    driver->rx_dma = &platform::ll_drivers::dma::dma2_stream2;
    driver->tx_dma = &platform::ll_drivers::dma::dma2_stream7;
  }

  template<>
  inline void attach_dma<USART2>(STM32UartDriver* driver)
  {
    //Enable peripheral clock
    rcc_periph_clock_enable(RCC_DMA1);

    //Enable nvic interrupt for dma stream
    nvic_enable_irq(NVIC_DMA1_STREAM5_IRQ);
    nvic_enable_irq(NVIC_DMA1_STREAM6_IRQ);
    
    //Assing dma channel handler
    driver->rx_dma = &platform::ll_drivers::dma::dma1_stream5;
    driver->tx_dma = &platform::ll_drivers::dma::dma1_stream6;
  }

  template<>
  constexpr STM32UartDriver* get_driver<USART1>()
  {
    return &uart1;
  }

  template<>
  constexpr STM32UartDriver* get_driver<USART2>()
  {
    return &uart2;
  }
  //USART1_END
}