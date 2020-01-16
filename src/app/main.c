#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <led.h>
#include <target.h>
#include <sys_timer.h>

volatile uint32_t tmp = 0;

static led_t fault_led;
static timer_t led_timer;

void sys_tick_handler(void)
{
  // if (++tmp == 1000) {
  //   led_toggle(&fault_led);

  //   tmp = 0;
  // }
  timers_trigger();
}

static void rcc_setup()
{
  //Clock setup
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);

}

static void systick_run()
{
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(8999);
  systick_interrupt_enable();
  systick_counter_enable();
}

void main_led_toggle(void* context)
{
  led_toggle(&fault_led);
    timer_create(&led_timer, 1000, main_led_toggle, (void*)0);
}

int main()
{
  rcc_setup();

  fault_led.gpiox = FAULT_LED_PORT;
  fault_led.pin_mask = FAULT_LED_PIN;
  fault_led.active_on = FAULT_LED_ACTIVE_ON;

  led_init(&fault_led);
  led_set_state(&fault_led, LED_STATE_ON);

  timers_init();
  timer_create(&led_timer, 1000, main_led_toggle, (void*)0);
  
  
  systick_run();

  while(1)
  {


  }
}