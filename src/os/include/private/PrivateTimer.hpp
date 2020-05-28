#pragma once

#include <stdint.h>
#include <Timer.hpp>

namespace os::timer
{
  void init();
  void add_timer(Timer* timer);
  void check_timers();
}