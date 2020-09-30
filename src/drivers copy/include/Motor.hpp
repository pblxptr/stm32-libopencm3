#pragma once

#include <stdint.h>

namespace drivers
{
  class Motor
  {
    uint32_t pwm_timer_;
    uint8_t thrust_;
  public:
    explicit Motor(uint32_t timer, uint32_t timer_channel);
    void start();
    void soft_start();
    void stop();
    void set_thrust(uint8_t power);
    uint8_t get_thrust() const;
  };
}