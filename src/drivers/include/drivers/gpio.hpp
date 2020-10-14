#pragma once

#include <stdint.h>

namespace drivers::gpio
{
  enum class Mode { INPUT, OUTPUT, AF, ANALOG };
  enum class PullUpDown { NONE, PULLUP, PULLDOWN };

  struct HwGpioConfig {
    uint32_t port;
    uint32_t pin;
  };

  template<
    auto _gpio_id,
    Mode _mode,
    PullUpDown _pupd
  >
  struct GpioDriverConfig
  {
    static constexpr uint32_t gpio_id = _gpio_id;
    static constexpr Mode mode = _mode;
    static constexpr PullUpDown pupd = _pupd; 
  };

  //TOOD: Add set on low or high
  struct GpioDriver
  {
    uint32_t port_;
    uint32_t pin_;

    GpioDriver(uint32_t port, uint32_t pin)
      : port_(port)
      , pin_(pin)
      {}
  };
}