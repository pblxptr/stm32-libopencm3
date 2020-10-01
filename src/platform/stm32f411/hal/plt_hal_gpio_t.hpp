#pragma once

extern "C" {
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/stm32/rcc.h>
}

#include <drivers/gpio.hpp>

namespace 
{
  template<drivers::gpio::Mode Mode>
  constexpr auto convert_mode()
  {
    if constexpr (Mode == drivers::gpio::Mode::INPUT)
      return GPIO_MODE_INPUT;
    else if constexpr (Mode == drivers::gpio::Mode::OUTPUT)
      return GPIO_MODE_OUTPUT;
    else if constexpr(Mode == drivers::gpio::Mode::ANALOG)
      return GPIO_MODE_ANALOG;
    else 
      return GPIO_MODE_AF;
  }

  template<drivers::gpio::PullUpDown PuPd>
  constexpr auto convert_pupd()
  {
    if constexpr (PuPd == drivers::gpio::PullUpDown::PULLDOWN)
      return GPIO_PUPD_PULLDOWN;
    else if constexpr (PuPd == drivers::gpio::PullUpDown::PULLUP)
      return GPIO_PUPD_PULLUP;
    else 
      return GPIO_PUPD_NONE;
  }
}

namespace platform::hal::gpio
{ 
  template<class TGpioDriver> 
  void setup_t()
  {
    using Driver_t = TGpioDriver;
    using Pinout_t = typename Driver_t::pinout;

    constexpr auto mode = convert_mode<Driver_t::mode>();
    constexpr auto pupd = convert_pupd<Driver_t::pupd>();

    gpio_mode_setup(Pinout_t::port, mode, pupd, Pinout_t::pin);
  }

  template<class TGpioDriver>
  void set_t()
  {
    using Driver_t = TGpioDriver;
    using Pinout_t = typename Driver_t::pinout;

    gpio_set(Pinout_t::port, Pinout_t::pin);
  }

  template<class TGpioDriver>
  void clear_t()
  {
    using Driver_t = TGpioDriver;
    using Pinout_t = typename Driver_t::pinout;

    gpio_clear(Pinout_t::port, Pinout_t::pin);
  }
}