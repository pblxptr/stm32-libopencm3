#pragma once

#include <stdint.h>

namespace drivers {
  class Led
  {
  public:
    enum class ActiveOn : uint8_t { LOW, HIGH };
    enum class State : uint8_t { OFF, ON };
  private:
    uint32_t gpiox_;
    uint32_t pin_;
    ActiveOn active_on_;
  
  public:
    Led(uint32_t gpiox, uint32_t pin, ActiveOn active_on);

    void toggle();
    void set_state(State state);
  };
}