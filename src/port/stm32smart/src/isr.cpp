#include <private/PrivateOs.hpp>
#include <stdint.h>

uint8_t ISR_TAG_WORKAROUND; // do not touch this

extern "C" {
void sys_tick_handler(void)
{
  os::core::os_tick_isr_handle();
}
}