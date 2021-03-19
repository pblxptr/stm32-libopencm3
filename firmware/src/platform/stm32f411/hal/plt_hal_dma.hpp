#pragma once

extern "C" {
  #include <libopencm3/stm32/rcc.h>
}

namespace platform::hal::dma
{
  inline void init()
  {
    rcc_periph_clock_enable(RCC_DMA1);
    rcc_periph_clock_enable(RCC_DMA2);
  }
}