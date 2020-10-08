#include <ll_dma_if.hpp>

extern "C" {
  #include <libopencm3/stm32/dma.h>
}

namespace platform::ll_drivers::dma
{
  DmaStream dma2_stream5;
  DmaStream dma2_stream6;
}

extern "C" {
  __attribute__((naked)) void dma2_stream5_isr()
  {
    using namespace platform::ll_drivers::dma;
    auto* dma = &dma2_stream5;
    dma->fwd_isr(dma->fwd_isr_ctx);

    //TODO: Clean after interrutp 
  }

  __attribute__((naked)) void dma2_stream6_isr()
  {
    using namespace platform::ll_drivers::dma;
    auto* dma = &dma2_stream6;
    dma->fwd_isr(dma->fwd_isr_ctx);

    //TODO: Clean after interrutp 
  }
}
