#pragma once

extern "C" {
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/stm32/rcc.h>
}

#include <drivers/gpio.hpp>

namespace {
  constexpr drivers::gpio::Pinout GPIOS[] = {
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

namespace platform::peripherals::gpio
{
  constexpr auto gpios() 
  {
    return GPIOS;
  }

  constexpr auto gpios_num()
  {
    return sizeof(GPIOS) / sizeof(GPIOS[0]);
  }
}