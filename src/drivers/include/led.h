#pragma once 

#include <stdint.h>

// EXAMPLE OF USE // 
/*
  - Setup RCC 

  - Setup leds: 
  fault_led.gpiox = FAULT_LED_PORT;
  fault_led.pin_mask = FAULT_LED_PIN;
  fault_led.active_on = FAULT_LED_ACTIVE_ON;

  status_led.gpiox = STATUS_LED_PORT;
  status_led.pin_mask = STATUS_LED_PIN;
  status_led.active_on = STATUS_LED_ACTIVE_ON;

  operational_led.gpiox = OPERATIONAL_LED_PORT;
  operational_led.pin_mask = OPERATIONAL_LED_PORT_LED_PIN;
  operational_led.active_on = OPERATIONAL_LED_PORT_LED_ACTIVE_ON;

  led_init(&fault_led);
  led_init(&status_led);
  led_init(&operational_led);

  led_toggle(&fault_led);
  led_toggle(&status_led);
  led_toggle(&operational_led);

  delay_ms(1000);

  led_toggle(&fault_led);
  led_toggle(&status_led);
  led_toggle(&operational_led);

*/


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