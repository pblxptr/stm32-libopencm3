#pragma once

#include <gpio.hpp>
#include <platform_impl_gpio.hpp>

namespace platform::gpio
{
  template<int GPIO_ID>
  constexpr drivers::gpio::Gpio_cfg get_cfg()
  {
    static_assert(GPIO_ID < sizeof(platform::gpio::gpios) / sizeof(drivers::gpio::Gpio_cfg), "Inavlid GPIO selecected.");

    return platform::gpio::gpios[GPIO_ID];
  }
}