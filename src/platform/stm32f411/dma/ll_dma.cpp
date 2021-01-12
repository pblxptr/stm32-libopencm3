#include <ll_dma.hpp>

extern "C" {
  #include <libopencm3/stm32/dma.h>
}

namespace {
  using namespace platform::ll_drivers::dma;

  static void handle_isr(DmaStream* dma)
  {
    using namespace platform::ll_drivers::dma;

    auto* func_ctx = dma->fwd_isr_ctx;

    volatile const uint16_t number_of_data = dma_get_number_of_data(dma->dma, dma->stream);

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

namespace platform::ll_drivers::dma
{
  DmaStream dma1_stream5{DMA1, DMA_STREAM5};
  DmaStream dma1_stream6(DMA1, DMA_STREAM6);

  DmaStream dma2_stream2{DMA2, DMA_STREAM2};
  DmaStream dma2_stream7{DMA2, DMA_STREAM7};
}

extern "C" {
  void dma1_stream5_isr() { handle_isr(&dma1_stream5); }
  void dma1_stream6_isr() { handle_isr(&dma1_stream6); }
  void dma2_stream2_isr() { handle_isr(&dma2_stream2); }
  void dma2_stream7_isr() { handle_isr(&dma2_stream7); }
}