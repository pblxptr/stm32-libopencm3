#include <hal/exti.h>

void hal_exti_configure(hal_exti_config_t* cfg)
{
  exti_select_source(cfg->pin, cfg->port);
  exti_set_trigger(cfg->pin, (enum exti_trigger_type)cfg->trigger_type);
  exti_enable_request(cfg->pin);
  nvic_enable_irq(cfg->_isr);
}

void hal_exti_complete_request(uint32_t exti)
{
    exti_reset_request(exti);
}