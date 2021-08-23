#include <os/internal/timer_internal.hpp>
#include <os/timer.hpp>

#include <stdint.h>
#include <functional>
#include <atomic>

using namespace os::timer;
using namespace utils::containers;

namespace {
  std::atomic<ticks_t> ticks = 0; //1 tick -> 1 millisecond
  List timers {};

  void add_timer(os::timer::Timer* new_timer)
  {
    if (timers.empty())
    {
      timers.append(make_link(new_timer));

      return;
    }

    const auto iter = std::find_if(timers.begin(), timers.end(), [=](const auto& x)
    {
      const Timer* timer = container_of(&x, Timer, node);
      
      return new_timer->timeout <= timer->timeout;
    });

    if (iter != timers.end())
    {
      timers.insert(iter, make_link(new_timer));
    }
    else
    {
      timers.append(make_link(new_timer));
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

    auto iter = std::find_if(timers.begin(), timers.end(), [=](const auto& x)
    {
      const Timer* timer = container_of(&x, Timer, node);
      
      return timer->timeout <= ticks;
    });

    if (iter == timers.end())
    {
      return;
    }

    Timer* timer = container_of(it_to_ptr(iter), Timer, node);

    const ticks_t substract_ticks = timer->timeout;

    dispatch_timer(timer);
    timers.erase(iter);

    update_timers(substract_ticks);
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
  void request_timer(Timer* timer, const delay_t& delay, timeout_cb_t cb)
  {
    if (timer == nullptr)
      return;
    
    timer->cb = cb;
    timer->timeout = ticks + delay.count();

    add_timer(timer);
  }

  void wait(const delay_t& delay)
  {
    const auto delay_ticks = ticks + delay.count();
    ticks_t current_ticks;

    do {
      current_ticks = ticks;
    } while(current_ticks < delay_ticks);
  }
}
