#include <stdint.h>
#include <target.h>

extern void sys_tick_isr_handler();
extern void hal_exti_isr(uint32_t);

void sys_tick_handler(void)
{
  sys_tick_isr_handler();
}

//encoder left 
void exti9_5_isr(void)
{
  hal_exti_isr(ENCODER_COUNTER_CLOCKWISE_DIRECTION_PIN);
}

//encoder right 
void exti0_isr(void)
{
  hal_exti_isr(ENCODER_CLOCKWISE_DIRECTION_PIN);
}

//encoder push
void exti4_isr(void)
{
  hal_exti_isr(ENCODER_BUTTON_PIN);
}
