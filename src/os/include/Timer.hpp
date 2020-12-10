#pragma once

#include <stdint.h>
#include <utils/list.hpp>

namespace os::timer 
{
  using ticks_t = uint32_t;
  using cb_t = void();

  struct TimerHandle 
  {
    ticks_t ticks_rem;
    cb_t* cb;
    utils::containers::ListNode_t node;
  };

  void create(TimerHandle* thandle, ticks_t dealy, cb_t* cb);
  ticks_t now();
  void wait(ticks_t delay);

}