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
    auto GpioId,
    Mode GMode,
    PullUpDown PuPd,
    auto AfId = -1
  >
  struct GpioDriverConfig
  {
    static constexpr uint32_t gpio_id = GpioId;
    static constexpr Mode mode = GMode;
    static constexpr PullUpDown pupd = PuPd; 
    static constexpr int32_t af_id = AfId;
  };

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