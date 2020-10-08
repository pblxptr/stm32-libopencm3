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

  //USART1
  template<>
  inline void configure_gpio<USART1>()
  {
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO2);
	  gpio_set_af(GPIOA, GPIO_AF7, GPIO1 | GPIO2);
  }

  template<>
  inline void configure_interrupts<USART1>()
  {
    nvic_enable_irq(NVIC_USART1_IRQ);
  }

  template<>
  inline void configure_dma<USART1>(STM32UartDriver* driver)
  {
    rcc_periph_clock_enable(RCC_DMA2);
    nvic_enable_irq(NVIC_DMA2_STREAM2_IRQ);
    dma_stream_reset(DMA2, DMA_STREAM2);
    dma_set_priority(DMA2, DMA_STREAM2, DMA_SxCR_PL_MEDIUM);
    dma_set_memory_size(DMA2, DMA_STREAM2, DMA_SxCR_MSIZE_8BIT);
    dma_set_peripheral_size(DMA2, DMA_STREAM2, DMA_SxCR_PSIZE_8BIT);
    dma_enable_memory_increment_mode(DMA2, DMA_STREAM2);
    dma_enable_circular_mode(DMA2, DMA_STREAM2);
    dma_set_transfer_mode(DMA2, DMA_STREAM2, DMA_SxCR_DIR_PERIPHERAL_TO_MEM);
    dma_set_peripheral_address(DMA2, DMA_STREAM2, reinterpret_cast<uint32_t>(&USART1_DR));
    dma_enable_transfer_complete_interrupt(DMA1, DMA_STREAM2);
    dma_channel_select(DMA2, DMA_STREAM2, DMA_SxCR_CHSEL_4);

    driver->rx_dma = &platform::ll_drivers::dma::dma2_stream5;
    driver->tx_dma = &platform::ll_drivers::dma::dma2_stream6;
  }

  template<>
  constexpr STM32UartDriver* get_driver<USART1>()
  {
    return &uart1;
  }
  //USART1_END
}