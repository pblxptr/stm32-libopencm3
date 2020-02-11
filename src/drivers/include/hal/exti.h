#pragma once 

#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>

typedef enum _hal_exti_trigger_t_ {
	HAL_EXTI_TRIGGER_RISING,
	HAL_EXTI_TRIGGER_FALLING,
	HAL_EXTI_TRIGGER_BOTH,
} hal_exti_trigger_t;

typedef void (exti_cb_t)();

#define HAL_EXTI_LINE_0  0
#define HAL_EXTI_LINE_1  0
#define HAL_EXTI_LINE_2  0
#define HAL_EXTI_LINE_3  0
#define HAL_EXTI_LINE_4  0
#define HAL_EXTI_LINE_5  0
#define HAL_EXTI_LINE_6  0
#define HAL_EXTI_LINE_7  0
#define HAL_EXTI_LINE_8  0
#define HAL_EXTI_LINE_9  0
#define HAL_EXTI_LINE_10 10
#define HAL_EXTI_LINE_11 11
#define HAL_EXTI_LINE_12 12
#define HAL_EXTI_LINE_13 13
#define HAL_EXTI_LINE_14 14
#define HAL_EXTI_LINE_15 15

typedef struct _hal_exti_setup_t_ {
    uint32_t port;
    uint32_t exti;
    hal_exti_trigger_t trigger_type;
    exti_cb_t* cb;
    uint32_t _isr;
} hal_exti_config_t;

#define HAL_EXTI_INIT_STRUCT(TARGET, EXTI, PORT, HANDLE) \
    (TARGET)->port = PORT; \
    (TARGET)->exti = EXTI; \
    (TARGET)->trigger_type = HAL_EXTI_TRIGGER_BOTH; \
    (TARGET)->_isr = (NVIC_##EXTI##_IRQ); \
    (TARGET)->cb = (HANDLE)

void hal_exti_configure(hal_exti_config_t* cfg)
{
  exti_select_source(cfg->exti, cfg->port);
  exti_set_trigger(cfg->exti, cfg->trigger_type);
  exti_enable_request(cfg->exti);
  nvic_enable_irq(cfg->_isr);
}

void hal_exti_isr(uint32_t line)
{
    exti_cb_t* cb = callbacks[line];    

    if (cb != NULL) {
        cb();
    }
}