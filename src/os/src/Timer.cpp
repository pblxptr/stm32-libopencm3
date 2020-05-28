#include <private/PrivateTimer.hpp>
#include <List.hpp>

using utils::containers::List_t;
using os::timer::Timer;

namespace {
  constexpr os::timer::ticks_t MAX_DELAY = 10000;
  constexpr os::timer::ticks_t MAX_UNSYNCH_TICKS = 20000;

  static os::timer::ticks_t ticks_unsynch = 0;
  static os::timer::ticks_t ticks_counter = 0;

  static utils::containers::List_t timers_list{};

  static void trigger_expired();
  static void trigger_all();
  static void dispatch(Timer* timer);
  static void update_ticks_for_all_timers();

  void trigger_expired()
  {
    auto it = timers_list.begin();

    if (it == timers_list.end())
      return;
    
    Timer* t = container_of(&*it, Timer, node);

    if (ticks_unsynch >= t->ticks_rem)
    {
      dispatch(t);
      timers_list.erase(it);
      update_ticks_for_all_timers();
    }
  }
  
  void trigger_all()
  {
    for (auto it = timers_list.begin(); it != timers_list.end(); )
    {
      Timer* t = container_of(&*it, Timer, node);
      dispatch(t);
      it = timers_list.erase(it);
    }

    ticks_unsynch = 0;
  }

  void dispatch(Timer* timer)
  {
    timer->cb();
  }

  void update_ticks_for_all_timers()
  {
    for (auto& it : timers_list)
    {
      Timer* t = container_of(&it, Timer, node);

      if (ticks_unsynch >= t->ticks_rem)
        t->ticks_rem = 0;
      else 
        t->ticks_rem -= ticks_unsynch;
    }

    ticks_unsynch = 0;
  }
}

namespace os::timer 
{
  //Api
  void create(Timer* timer, ticks_t delay, cb_t* cb) 
  {
    timer->ticks_rem = ticks_unsynch + delay;
    timer->cb = cb;

    add_timer(timer);
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

  //Private 
  void init() {}
  void add_timer(Timer* timer)
  {
    if (timers_list.empty())
    {
      timers_list.append(make_link_ptr(*timer));

      return;
    }
    
    auto it = timers_list.begin();

    while (it != timers_list.end())
    {
      Timer* t = container_of(&it, Timer, node);
      
      if (t->ticks_rem >= timer->ticks_rem)
        break;
      
      ++it;
    }

    timers_list.insert(it, make_link_ptr(*timer));
  }

  void check_timers()
  {
    ++ticks_counter;
    ++ticks_unsynch;

    if (ticks_unsynch >= MAX_UNSYNCH_TICKS)
    {
      trigger_all();
    }
    else 
    {
      trigger_expired();
    }
  }
}