#pragma once

#include <drivers/gpio.hpp>
#include <ll_gpio.hpp>

extern "C" {
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/stm32/rcc.h>
}

namespace 
{
  using namespace drivers::gpio;

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
  inline void init()
  {
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOD);
  }

  template<class TConfig>
  GpioDriver* setup()
  {
    using Config = TConfig;

    //Get driver
    constexpr auto* driver = platform::ll_drivers::gpio::get_driver<Config::gpio_id>();
    static_assert(driver != nullptr);

    //Set mode
    gpio_mode_setup(
      driver->port_, 
      convert_mode<Config::mode>(),
      convert_pupd<Config::pupd>(),
      driver->pin_
    );

    return driver;
  }

  void set(GpioDriver* driver)
  {
    gpio_set(driver->port_, driver->pin_);
  }

  void toggle(GpioDriver* driver)
  {
    gpio_toggle(driver->port_, driver->pin_);
  }

  void clear(GpioDriver* driver)
  {
    gpio_clear(driver->port_, driver->pin_);
  }
  
}