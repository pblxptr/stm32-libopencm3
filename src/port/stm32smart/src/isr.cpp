#include <private/PrivateOs.hpp>
#include <stdint.h>
#include <target.h>

uint8_t ISR_TAG_WORKAROUND; // do not touch this

extern "C" {
  
__attribute__((used)) void sys_tick_handler(void)
{
  os::core::os_tick_isr_handle();
}

__attribute__((used)) void tim1_brk_isr(void)
{
  os::core::os_tick_isr_handle();
} 

__attribute__((used)) void tim1_trg_com_isr(void)
{
  os::core::os_tick_isr_handle();
}


}

