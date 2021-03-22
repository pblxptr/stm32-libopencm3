#include <os/internal/timer_internal.hpp>
#include <os/timer.hpp>

#include <stdint.h>
#include <functional>

using namespace os::timer;
using namespace utils::containers;

namespace {
  ticks_t ticks = 0; //1 tick -> 1 millisecond
  List timers;

  void add_timer(os::timer::Timer* new_timer)
  {
    if (timers.empty())
    {
      timers.append(make_link(new_timer));

      return;
    }

    for (auto iter = timers.begin(); iter != timers.end();  ++iter)
    {
      const Timer* timer = container_of(it_to_ptr(iter), Timer, node); 

      if (new_timer->timeout <= timer->timeout)
      {
        timers.insert(iter, make_link(new_timer));

        return;
      }
    }
  }

  void dispatch_timer(Timer* timer)
  {
    if (timer->cb != nullptr)
    {
      std::invoke(timer->cb);
    }
  }

  void update_timers(const ticks_t substract_ticks)
  {
    for (auto& t : timers)
    {
      Timer* timer = container_of(&t, Timer, node);
      timer->timeout -= substract_ticks;
    }
  }

  void check_timers()
  {
    if (timers.empty())
    {
      return;
    }

    for (auto iter = timers.begin(); iter != timers.end();  ++iter)
    {
      Timer* timer = container_of(it_to_ptr(iter), Timer, node);

      if (timer->timeout <= ticks)
      {
        const ticks_t substract_ticks = timer->timeout;

        dispatch_timer(timer);
        timers.erase(iter);
        update_timers(substract_ticks);

        return;
      }
    }
  }

}

namespace os::timer 
{
  // INTERNAL
  void init()
  {
  }

  void notify_tick()
  {
    ++ticks;

    check_timers();
  }

  // PUBLIC
  void request_timer(Timer* timer, const std::chrono::milliseconds& duration, timeout_cb_t cb)
  {
    if (timer == nullptr)
      return;
    
    timer->cb = cb;
    timer->timeout = ticks + duration.count();

    add_timer(timer);
  }

  void request_timer(Timer* timer, const std::chrono::seconds& duration, timeout_cb_t cb)
  {
    request_timer(timer, std::chrono::duration_cast<std::chrono::milliseconds>(duration), cb);
  }

  void request_timer(Timer* timer, const std::chrono::minutes& duration, timeout_cb_t cb)
  {
    request_timer(timer, std::chrono::duration_cast<std::chrono::milliseconds>(duration), cb);
  }
}
