#include <stdint.h>
#pragma once

namespace drivers::gpio
{
  struct Gpio_cfg {
    uint32_t port;
    uint32_t pin;
  };

  class Gpio {
    public:
      Gpio(const Gpio_cfg&);
  };
}