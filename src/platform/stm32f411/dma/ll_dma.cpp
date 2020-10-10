#include <ll_dma_if.hpp>

extern "C" {
  #include <libopencm3/stm32/dma.h>
}

namespace platform::ll_drivers::dma
{
  DmaStream dma2_stream2{DMA2, DMA_STREAM2};
}

extern "C" {
  void dma2_stream2_isr()
  {
    using namespace platform::ll_drivers::dma;

    auto* dma = &dma2_stream2;
    auto* func_ctx = dma->fwd_isr_ctx;

    //TODO: Clean after interrutp 
    dma_clear_interrupt_flags(dma->dma, dma->stream, DMA_ISR_FLAGS);

    if(dma->fwd_isr == nullptr)
      return;

    //Call forward function
    dma->fwd_isr(func_ctx);
  }
}