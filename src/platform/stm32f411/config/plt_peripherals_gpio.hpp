#pragma once

extern "C" {
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/stm32/rcc.h>
}

#include <drivers/gpio.hpp>

namespace platform::peripherals::gpio
{
  constexpr drivers::gpio::Pinout gpios[] = {
    {
      GPIOC,
      GPIO13
    },
    {
      GPIOA,
      GPIO2
    }
  };
}