#include <internal/timer_internal.hpp>
#include <timer.hpp>

#include <stdint.h>
#include <functional>

#include <list.hpp>

using namespace os::timer;
using namespace os::utils;

namespace {
  ticks_t ticks = 0; //1 tick -> 1 millisecond
  List timers;

//   void add_timer(os::timer::Timer* new_timer)
//   {
//     if (list_empty(&timers))
//     {
//       list_append(&timers, &new_timer->list);

//       return;
//     }

//     auto iter = list_begin(&timers);

//     while (iter != list_end(&timers))
//     {
//       const Timer* timer = container_of(iter, Timer, list); 

//       if (new_timer->timeout <= timer->timeout)
//       {
//         list_insert(iter, &new_timer->list);

//         return;
//       }

//       iter = list_next(iter);
//     }
//   }

//   void dispatch_timer(Timer* timer)
//   {
//     if (timer->cb != nullptr)
//     {
//       std::invoke(timer->cb);
//     }
//   }

//   void update_timers(const ticks_t substract_ticks)
//   {
//     List::iter_t iter = list_begin(&timers);
    
//     while (iter != list_end(&timers))
//     {
//       Timer* timer = container_of(iter, Timer, list);
//       timer->timeout -= substract_ticks;

//       iter = list_next(iter);
//     }
//   }

//   void check_timers()
//   {
//     if (list_empty(&timers))
//     {
//       return;
//     }

//     auto iter = list_begin(&timers);

//     while (iter != list_end(&timers))
//     {
//       Timer* timer = container_of(iter, Timer, list);

//       if (timer->timeout <= ticks)
//       {
//         const ticks_t substract_ticks = timer->timeout;

//         dispatch_timer(timer);
//         list_remove(iter);
//         update_timers(substract_ticks);

//         return;
//       }

//       iter = list_next(iter);
//     }
//   }
// }

// namespace os::timer 
// {
//   // INTERNAL
//   void init()
//   {
//     list_init(&timers);
//   }

//   void notify_tick()
//   {
//     ++ticks;

//     check_timers();
//   }

//   // PUBLIC
//   void request_timer(Timer* timer, const std::chrono::milliseconds& duration, timeout_cb_t cb)
//   {
//     if (timer == nullptr)
//       return;
    
//     timer->cb = cb;
//     timer->timeout = ticks + duration.count();

//     add_timer(timer);
//   }

//   void request_timer(Timer* timer, const std::chrono::seconds& duration, timeout_cb_t* cb)
//   {
//     request_timer(timer, std::chrono::duration_cast<std::chrono::milliseconds>(duration), cb);
//   }

//   void request_timer(Timer* timer, const std::chrono::minutes& duration, timeout_cb_t* cb)
//   {
//     request_timer(timer, std::chrono::duration_cast<std::chrono::milliseconds>(duration), cb);
//   }
}
