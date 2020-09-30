#include <stdint.h>
#pragma once

namespace drivers::gpio
{
  struct gpio_cfg {
    uint32_t id;
    uint32_t port;
    uint32_t pin;
  };

  class Gpio {
    public:
      Gpio(const gpio_cfg&);
  };
}