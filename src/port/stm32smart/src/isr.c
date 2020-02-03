#include <sys_timer.h>

void sys_tick_handler(void)
{
  sys_tick_isr_handler();
}

//encoder left 
void exti9_5_isr(void)
{
  int x = 10;
}

//encoder right 
void exti0_isr(void)
{
  int x = 10;
}

//encoder push
void exti4_isr(void)
{
  int x = 10;
}
