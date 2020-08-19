#include <private/PrivateOs.hpp>
#include <stdint.h>

uint8_t ISR_TAG_WORKAROUND; // do not touch this

extern "C" {
void sys_tick_handler(void)
{
  os::core::os_tick_isr_handle();
}

void tim1_brk_isr(void)
{
  os::core::os_tick_isr_handle();
} 

void tim1_trg_com_isr(void)
{
  os::core::os_tick_isr_handle();
}

// void tim1_up_isr(void)
// {
//   os::core::os_tick_isr_handle();
// } 
// void tim1_cc_isr(void)
// {
//   os::core::os_tick_isr_handle();
// } 

}

