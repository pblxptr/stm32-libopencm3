#pragma once 

#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>

typedef enum _hal_exti_trigger_t_ {
	HAL_EXTI_TRIGGER_RISING,
	HAL_EXTI_TRIGGER_FALLING,
	HAL_EXTI_TRIGGER_BOTH,
} hal_exti_trigger_t;

typedef struct _hal_exti_setup_t_ {
    uint32_t port;
    uint32_t pin;
    hal_exti_trigger_t trigger_type;
    uint32_t _isr;
} hal_exti_config_t;

#define HAL_EXTI_INIT_STRUCT(TARGET, PORT, PIN, ISR) \
    (TARGET)->port = PORT; \
    (TARGET)->pin = PIN; \
    (TARGET)->trigger_type = HAL_EXTI_TRIGGER_BOTH; \
    (TARGET)->_isr = ISR; \

void hal_exti_configure(hal_exti_config_t* cfg);
void hal_exti_complete_request(uint32_t exti);
void hal_exti_isr(uint32_t pin); // implement in app code 