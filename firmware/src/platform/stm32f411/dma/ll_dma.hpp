#pragma once

#include <stdint.h>

namespace platform::ll_drivers::dma
{
  using dma_flags_t = uint32_t;
  using dma_irq_t = void(*)(void*, dma_flags_t);

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
  extern DmaStream dma1_stream5;
  extern DmaStream dma1_stream6;

  extern DmaStream dma2_stream2;
  extern DmaStream dma2_stream7;
}