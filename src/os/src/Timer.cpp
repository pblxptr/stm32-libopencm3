#include <private/PrivateTimer.hpp>

namespace {
  constexpr os::timer::ticks_t MAX_DELAY = 10000;

  static os::timer::ticks_t ticks_unsynch = 0;
  static os::timer::ticks_t ticks_counter = 0;
}

namespace os::timer 
{
  //Api 
  void create(Timer* thandle, ticks_t delay, cb_t* cb) 
  {
  }

  ticks_t now() 
  {
    return ticks_counter;
  }
  
  void wait(ticks_t delay) 
  {
    uint32_t wait_time = now() + delay;

    while (wait_time >= now());
  }

  void init() {}
  void update() 
  {
    ++ticks_counter;
  }
}