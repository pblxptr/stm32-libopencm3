#pragma once

#include <stdint.h>

namespace drivers::gpio
{
  enum class Mode { INPUT, OUTPUT, AF, ANALOG };
  enum class PullUpDown { NONE, PULLUP, PULLDOWN };

  struct Pinout {
    uint32_t port;
    uint32_t pin;
  };

  struct GpioDriver
  {
    Pinout pinout;
    Mode mode;
    PullUpDown pd;
  };


  template<uint32_t _port, uint32_t _pin>
  struct StaticPinout 
  {
    static constexpr uint32_t port = _port;
    static constexpr uint32_t pin = _pin;
  };

  template<uint32_t _port, uint32_t _pin, Mode _mode, PullUpDown _pullupdown>
  struct StaticGpioDriver
  {
    using pinout = StaticPinout<_port, _pin>;
    static constexpr Mode mode = _mode;
    static constexpr PullUpDown pupd = _pullupdown;
  };
}