#pragma once 
#include <stdint.h>
#include <list.h>

typedef void(timer_cb_t)(void* context);

typedef uint32_t sys_ticks_t;
typedef uint16_t sys_delay_t;

typedef struct _timer_t {
  sys_ticks_t fire_on;
  timer_cb_t* cb;
  void* context;
  list_t _list;
} timer_t;

typedef timer_t* timer_handle_t; 

void sys_timer_create(timer_handle_t thandle, sys_delay_t delay, 
    timer_cb_t* cb, void* context);

sys_ticks_t sys_ticks_now();

//TODO: Hide functions listed belw.
void sys_timers_init(); // hide
void sys_tick_isr_handler(); //hide