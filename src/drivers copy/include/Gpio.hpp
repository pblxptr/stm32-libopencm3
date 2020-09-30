#pragma once

#include <stdint.h>

namespace drivers
{
  class Gpio
  {
    uint32_t gpiox_;
    uint32_t pin_;
  
  public:
    Gpio() = default;
    Gpio(uint32_t gpiox, uint32_t pin);
    void set();
    void clear();
    void toggle();
  };  
}