#pragma once

#include <drivers/gpio.hpp>
#include <stdint.h>

namespace {
  using namespace drivers::gpio;
}

namespace platform::ll_drivers::gpio
{
  constexpr uint32_t number_of_gpios = 48; //TODO: MOve to config
  extern GpioDriver gpios[number_of_gpios];

  template<uint32_t GPIO_ID>
  constexpr GpioDriver* get_driver()
  {
    return &gpios[GPIO_ID];
  }
}