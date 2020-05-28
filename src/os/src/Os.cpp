extern "C" {
  #include <libopencm3/stm32/rcc.h>
  #include <libopencm3/cm3/systick.h>
}

#include <private/PrivateTimer.hpp>

namespace os::core 
{
  void init() 
  {
    //Configure main clock.
    rcc_clock_setup_in_hse_8mhz_out_72mhz();

    //Configure systick subsystem.
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
    systick_set_reload(8999);

    //Configure timers subsystem.
    os::timer::init();
  }

  void run() 
  {
    //Run systick.
    systick_interrupt_enable();
    systick_counter_enable();
  }

  void os_tick_isr_handle()
  {
    os::timer::check_timers(); 
  }
}