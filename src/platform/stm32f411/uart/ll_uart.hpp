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
  inline void configure_uart_gpio<USART1>()
  {
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);
	  gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);
  }

  template<>
  inline void configure_interrupts<USART1>()
  {
    nvic_enable_irq(NVIC_USART1_IRQ);
  }

  template<>
  inline void configure_uart_dma<USART1>(STM32UartDriver* driver)
  {
    //Enable peripheral clock
    rcc_periph_clock_enable(RCC_DMA2);

    //Enable nvic interrupt for dma stream
    nvic_enable_irq(NVIC_DMA2_STREAM2_IRQ);
    nvic_enable_irq(NVIC_DMA2_STREAM7_IRQ);
    
    //Configure RX dma
    dma_disable_stream(DMA2, DMA_STREAM2);
    dma_stream_reset(DMA2, DMA_STREAM2);
    dma_set_peripheral_address(DMA2, DMA_STREAM2, (uint32_t) &USART1_DR);
    dma_channel_select(DMA2, DMA_STREAM2, DMA_SxCR_CHSEL_4);
    dma_set_priority(DMA2, DMA_STREAM2, DMA_SxCR_PL_MEDIUM);
    dma_set_memory_size(DMA2, DMA_STREAM2, DMA_SxCR_MSIZE_8BIT);
    dma_set_peripheral_size(DMA2, DMA_STREAM2, DMA_SxCR_PSIZE_8BIT);
    dma_enable_memory_increment_mode(DMA2, DMA_STREAM2);
    dma_enable_circular_mode(DMA2, DMA_STREAM2);
    dma_set_transfer_mode(DMA2, DMA_STREAM2, DMA_SxCR_DIR_PERIPHERAL_TO_MEM);

    //Configure TX dma
    dma_disable_stream(DMA2, DMA_STREAM7);
    dma_stream_reset(DMA2, DMA_STREAM7);
    dma_set_peripheral_address(DMA2, DMA_STREAM7, (uint32_t) &USART1_DR);
    dma_channel_select(DMA2, DMA_STREAM7, DMA_SxCR_CHSEL_4);
    dma_set_priority(DMA2, DMA_STREAM7, DMA_SxCR_PL_MEDIUM);
    dma_set_memory_size(DMA2, DMA_STREAM7, DMA_SxCR_MSIZE_8BIT);
    dma_set_peripheral_size(DMA2, DMA_STREAM7, DMA_SxCR_PSIZE_8BIT);
    dma_enable_memory_increment_mode(DMA2, DMA_STREAM7);
    dma_set_transfer_mode(DMA2, DMA_STREAM7, DMA_SxCR_DIR_MEM_TO_PERIPHERAL);
    
    //Assing dma channel handler
    driver->rx_dma = &platform::ll_drivers::dma::dma2_stream2;
    driver->tx_dma = &platform::ll_drivers::dma::dma2_stream7;
  }

  template<>
  constexpr STM32UartDriver* get_driver<USART1>()
  {
    return &uart1;
  }
  //USART1_END
}