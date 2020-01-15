#pragma once 

#include <stdint.h>

typedef enum _active_mode_t {
  LED_ACTIVE_LOW = 0,
  LED_ACTIVE_HIGH = 1
} active_mode_t;

typedef enum _led_state_t {
  LED_STATE_OFF = 0,
  LED_STATE_ON = 1
} led_state_t;

typedef struct _led_t {
  uint32_t gpiox;
  uint32_t pin_mask; 
  active_mode_t active_on;
} led_t;

typedef led_t* led_handle_t;

void led_init(led_handle_t handle);
void led_set_state(led_handle_t handle, led_state_t state);
void led_toggle(led_handle_t handle);