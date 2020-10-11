#pragma once

#include <drivers/gpio.hpp>
#include <stdint.h>

namespace {
  using namespace drivers::gpio;
}

namespace platform::ll_drivers::gpio
{
  extern GpioDriver drivers[];

  template<uint32_t GPIO_ID>
  constexpr GpioDriver* get_driver()
  {
    return &drivers[GPIO_ID];
  }
}