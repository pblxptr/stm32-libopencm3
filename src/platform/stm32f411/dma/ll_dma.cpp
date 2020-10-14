#include <ll_dma_if.hpp>

extern "C" {
  #include <libopencm3/stm32/dma.h>
}

namespace platform::ll_drivers::dma
{
  DmaStream dma2_stream2{DMA2, DMA_STREAM2};
  DmaStream dma2_stream7{DMA2, DMA_STREAM7};
}

extern "C" {
  void dma2_stream2_isr()
  {
    using namespace platform::ll_drivers::dma;

    const auto* dma = &dma2_stream2;
    auto* func_ctx = dma->fwd_isr_ctx;

    dma_flags_t flags{0};

    if (dma_get_interrupt_flag(dma->dma, dma->stream, DMA_TEIF))
    {
      flags |= DMA_TEIF;
    }
    else if (dma_get_interrupt_flag(dma->dma, dma->stream, DMA_TCIF))
    {
      flags |= DMA_TCIF;
    }

    dma_clear_interrupt_flags(dma->dma, dma->stream, DMA_ISR_FLAGS);

    //Call forward function
    if (dma->fwd_isr != nullptr)
    {
      dma->fwd_isr(func_ctx, flags);
    }
  }

  void dma2_stream7_isr()
  {
    using namespace platform::ll_drivers::dma;

    const auto* dma = &dma2_stream7;
    auto* func_ctx = dma->fwd_isr_ctx;

    dma_flags_t flags{0};

    if (dma_get_interrupt_flag(dma->dma, dma->stream, DMA_TEIF))
    {
      flags |= DMA_TEIF;
    }
    else if (dma_get_interrupt_flag(dma->dma, dma->stream, DMA_TCIF))
    {
      flags |= DMA_TCIF;
    }

    dma_clear_interrupt_flags(dma->dma, dma->stream, DMA_ISR_FLAGS);

    //Call forward function
    if (dma->fwd_isr != nullptr)
    {
      dma->fwd_isr(func_ctx, flags);
    }
  }
}