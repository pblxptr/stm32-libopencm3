#pragma once 

#include <libopencm3/stm32/gpio.h>

#define FAULT_LED_PORT       GPIOA
#define FAULT_LED_PIN        GPIO11
#define FAULT_LED_ACTIVE_ON  0 

#define STATUS_LED_PORT      GPIOB
#define STATUS_LED_PIN       GPIO5
#define STATUS_LED_ACTIVE_ON 0