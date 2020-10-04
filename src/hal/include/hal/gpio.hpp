#pragma once

#include<drivers/gpio.hpp>
#include<platform/hal/gpio.hpp>

namespace hal::gpio
{
  void init()
  {
    // platform::hal::gpio::init();
  }

  void setup(const drivers::gpio::GpioDriver& gpio)
  {
    platform::hal::gpio::setup(gpio);
  }

  void set(const drivers::gpio::GpioDriver& gpio)
  {
    platform::hal::gpio::set(gpio);
  }

  void clear(const drivers::gpio::GpioDriver& gpio)
  {
    platform::hal::gpio::clear(gpio);
  }
  
  //Template version
  template<class TGpioDriver> 
  void setup_t()
  {
    platform::hal::gpio::setup_t<TGpioDriver>();
  }

  template<class TGpioDriver> 
  void set_t()
  {
    platform::hal::gpio::set_t<TGpioDriver>();
  }

  template<class TGpioDriver> 
  void clear_t()
  {
    platform::hal::gpio::clear_t<TGpioDriver>();
  }
}