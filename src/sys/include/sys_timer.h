#pragma once 
#include <stdint.h>
#include <list.h>

typedef void(timer_cb_t)(void* context);

typedef uint16_t sys_ticks_t;

typedef struct _timer_t {
  sys_ticks_t fire_on;
  timer_cb_t* cb;
  void* context;
  list_t _list;
} timer_t;

typedef timer_t* timer_handle_t; 

void timer_create(timer_handle_t thandle, sys_ticks_t delay, 
    timer_cb_t* cb, void* context);

//TODO: Hide functions listed belw.
void timers_init(); // hide
void timers_trigger(); //hide