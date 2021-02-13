#pragma once

#include <platform/hal/dma.hpp>

namespace hal::dma
{
  inline void init()
  {
    platform::hal::dma::init();
  }
}