#include <sys_timer.h>
#include <list.h>
#include <stddef.h>

static list_t timers_list;
static sys_ticks_t ticks_counter; 
static sys_ticks_t timer_unsynch_ticks;
static uint16_t max_delay = 10000; //10s 

// PRIVATE FUNCTIONS DECLARATIONS // 
void timer_add(timer_handle_t thandle, uint16_t delay, 
    timer_cb_t* cb, void* context);
void update_timers();

// PUBLIC FUNCTIONS IMPLEMENTATIONS // 
void sys_timer_create(timer_handle_t thandle, sys_delay_t delay, 
    timer_cb_t* cb, void* context)
{
  if (delay > max_delay) {
    return;
  }

  timer_add(thandle, delay, cb, context);
}

// Can be called only from sys_init()
void sys_timers_init()
{
  ticks_counter = 0;
  timer_unsynch_ticks = 0;
  list_init(&timers_list);
}

//Can be called only from sys_tick_handler isr 
void sys_tick_isr_handler()
{
  ticks_counter++;

  list_t* iter = list_begin(&timers_list);

  if (list_end(&timers_list, iter)) {
    return; 
  }

  timer_t* timer = container_of(iter, timer_t, _list);

  if (++timer_unsynch_ticks >= timer->fire_on) {
    list_remove(iter);
    update_timers();

    if (timer->cb != NULL) {
      timer->cb(timer->context);
    }
  }
}

sys_ticks_t sys_ticks_now()
{
  return ticks_counter;
}

// PRIVATE FUNCTIONS IMPLEMENTATIONS // 
void timer_add(timer_handle_t thandle, sys_delay_t delay, 
    timer_cb_t* cb, void* context)
{
  thandle->fire_on = timer_unsynch_ticks + delay;
  thandle->cb = cb;
  thandle->context = context;

  list_init(&thandle->_list);

  list_t* iter = list_begin(&timers_list);

  if (!list_end(&timers_list, iter)) {
    do {
      timer_t* tnext = container_of(iter, timer_t, _list);

      if (thandle->fire_on < tnext->fire_on) {
        break;
      }

      iter = list_next(iter);

    } while(!list_end(&timers_list, iter));
  }

  list_insert(iter, &thandle->_list);
}

void update_timers()
{
  list_t* iter = list_begin(&timers_list);

  while (!list_end(&timers_list, iter)) {
    timer_t* tm = NULL;
    
    tm = container_of(iter, timer_t, _list);
    tm->fire_on -= timer_unsynch_ticks;
    
    iter = list_next(iter);
  }

  timer_unsynch_ticks = 0;
}