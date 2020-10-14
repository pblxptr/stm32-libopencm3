#pragma once

#include<drivers/gpio.hpp>
#include<platform/hal/gpio.hpp>

namespace hal::gpio
{
  void init()
  {
    platform::hal::gpio::init();
  }

  template<class TConfig>
  constexpr drivers::gpio::GpioDriver* setup()
  {
    return platform::hal::gpio::setup<TConfig>();
  }

  void set(drivers::gpio::GpioDriver* driver)
  {
    platform::hal::gpio::set(driver);
  }

  void toggle(drivers::gpio::GpioDriver* driver)
  {
    platform::hal::gpio::toggle(driver);
  }

  void clear(drivers::gpio::GpioDriver* driver)
  {
    platform::hal::gpio::clear(driver);
  }
}