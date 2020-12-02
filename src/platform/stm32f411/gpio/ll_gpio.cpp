#include <drivers/gpio.hpp>
#include <cstddef>
extern "C" {
  #include <libopencm3/stm32/gpio.h>
}

using namespace drivers::gpio;

namespace {
  #define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))
}

namespace platform::ll_drivers::gpio
{
  GpioDriver gpios[] = {
    {GPIOC, GPIO13},
    {GPIOA, GPIO5},
    {GPIOA, GPIO6},
    {GPIOA, GPIO7}
  };
}

