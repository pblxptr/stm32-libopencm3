#include <sys_timer.h>
#include <list.h>
#include <stddef.h>

static list_t timers_list;
static sys_ticks_t idle_ticks;

void timer_create(timer_handle_t thandle, uint16_t delay, 
    timer_cb_t* cb, void* context)
{
  list_t* iter = list_begin(&timers_list);
    
  if (!list_end(&timers_list, iter)) {
    //iterate 
  }

  thandle->fire_on = idle_ticks + delay;
  thandle->cb = cb;
  thandle->context = context;

  list_append(iter, &thandle->_list);
}

// Can be called only from sys_init()
void timers_init()
{
  list_init(&timers_list);
}

//Can be called only from sys_tick_handler isr 
void timers_trigger()
{
  list_t* iter = list_begin(&timers_list);

  if (list_end(&timers_list, iter)) {
    return; 
  }

  timer_t* timer = container_of(iter, timer_t, _list);
  timer_cb_t* cb = NULL;

  if (++idle_ticks >= timer->fire_on) {
    cb = timer->cb;
    list_remove(iter);
    idle_ticks = 0;
  }

  if (cb != NULL) {
    cb((void*)0);
  }
}