#include <timer.hpp>
#include <stdint.h>

namespace {
  using ticks_t = uint32_t;

  static ticks_t ticks = 0; //1 tick -> 1 millisecond
}

namespace os::timer 
{
  struct Timer
  {
    ticks_t timeout;
    timeout_cb_t* cb;
  };


  void request_timer(Timer* timer, const std::chrono::milliseconds& duration, timeout_cb_t* cb)
  {
    if (timer == nullptr)
      return;
    
    timer->cb = cb;

  }
  void request_timer(Timer* timer, const std::chrono::seconds& duration, timeout_cb_t* cb)
  {
    request_timer(timer, std::chrono::duration_cast<std::chrono::milliseconds>(duration), cb);
  }
  void request_timer(Timer* timer, const std::chrono::minutes& duration, timeout_cb_t* cb)
  {
    request_timer(timer, std::chrono::duration_cast<std::chrono::milliseconds>(duration), cb);
  }
}