#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <led.h>
#include <target.h>
#include <delay.h>
#include <libopencm3/cm3/nvic.h>
#include <gps.h>
#include <ec_bus.h>

led_t status_led;
gps_t gps;

static void rcc_setup()
{
  //Clock setup
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}

static void systick_run()
{
  //Required by timers 
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(8999);
  systick_interrupt_enable();
  systick_counter_enable();
}

int main()
{
  rcc_setup();
  sys_timers_init();
  systick_run();

  status_led.active_on = STATUS_LED_ACTIVE_ON;
  status_led.gpiox = FAULT_LED_PORT;
  status_led.pin_mask = FAULT_LED_PIN;
  led_init(&status_led);

  // gps_init(&gps);

  led_set_state(&status_led, LED_STATE_ON);

  delay_ms(2000);

  led_set_state(&status_led, LED_STATE_OFF);
  ec_bus_init();

AFIO_MAPR |= AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON;
  while(1)
  {
    // gps_task(&gps); 
    ec_bus_task();
  }
}