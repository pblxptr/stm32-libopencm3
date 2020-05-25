#pragma once

#include <stdint.h>

namespace os::timer 
{
  using ticks_t = uint32_t;
  using cb_t = void();

  struct Timer 
  {
    ticks_t ticks_rem;
    cb_t* cb;
  };

  void create(Timer* thandle, ticks_t dealy, cb_t* cb);
  ticks_t now();
  void wait(ticks_t delay);

}