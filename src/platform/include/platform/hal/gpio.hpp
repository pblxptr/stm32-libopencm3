#pragma once

#include<plt_hal_gpio.hpp>
#include<plt_hal_gpio_t.hpp>
#include <drivers/gpio.hpp>

namespace platform::hal::gpio
{
  void init();
  void setup(const drivers::gpio::GpioDriver& gpio);
  void set(const drivers::gpio::GpioDriver& gpio);
  void clear(const drivers::gpio::GpioDriver& gpio);
}