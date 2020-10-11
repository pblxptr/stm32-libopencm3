#include <drivers/gpio.hpp>
 
extern "C" {
  #include <libopencm3/stm32/gpio.h>
}

using namespace drivers::gpio;

namespace platform::ll_drivers::gpio
{
  GpioDriver drivers[] = {
    {GPIOC, GPIO13}
  };
}

