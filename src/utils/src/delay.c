#include <delay.h>
#include <stdint.h>

void delay_ms(sys_delay_t miliseconds)
{
  const uint32_t delay = sys_ticks_now() + miliseconds;

  while (delay >= sys_ticks_now());
}