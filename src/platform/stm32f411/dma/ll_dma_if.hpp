#pragma once

#include <stdint.h>

namespace platform::ll_drivers::dma
{
  using dma_irq_t = void(*)(void*);

  struct DmaStream
  {
    uint32_t dma;
    uint32_t stream;
    dma_irq_t fwd_isr;
    void* fwd_isr_ctx;

    DmaStream(uint32_t dma, uint32_t stream)
      : dma{dma}
      , stream{stream}
      , fwd_isr{nullptr}
      , fwd_isr_ctx{nullptr} {}
  };

  //TODO: Only for uart1
  extern DmaStream dma2_stream2;
}