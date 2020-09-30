#include <gpio.hpp>

extern "C" {
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/stm32/rcc.h>
}

namespace drivers::gpio
{
  Gpio::Gpio(const Gpio_cfg&)
  {
    
  }
}
