#include <sys_timer.h>

void sys_tick_handler(void)
{
  sys_tick_isr_handler();
}
