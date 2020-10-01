#pragma once

#include <drivers/gpio.hpp>
#include <plt_peripherals_gpio.hpp>
#include <plt_hal_gpio.hpp>

namespace platform::peripherals
{
  template<int GPIO_ID>
  constexpr drivers::gpio::Pinout get_config()
  {
    static_assert(GPIO_ID < sizeof(platform::peripherals::gpio::gpios) / sizeof(drivers::gpio::Pinout), "Inavlid GPIO selecected.");

    return platform::peripherals::gpio::gpios[GPIO_ID];
  }
}