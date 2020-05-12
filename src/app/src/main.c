#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <led.h>
#include <target.h>
#include <delay.h>
#include <libopencm3/cm3/nvic.h>
#include <gps.h>
#include <ec_bus.h>
#include <msg_gps_buffer.h>
#include <libopencm3/stm32/f1/timer.h>
#include <sys_timer.h>

led_t status_led;
gps_t gps;

// TODO: Verify double-endabled rcc for the same peripheral

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

#define OS_FLCK (72000000)
#define TIMER_FREQ (20000)

uint16_t duty_value_from_percentage(uint8_t percnt)
{
  return (percnt * (OS_FLCK / TIMER_FREQ)) / 100;
}

static sys_timer_t t1;
static uint16_t duty_percentage = 85;

void handle_timer(void* context)
{
  if (++duty_percentage <= 100)
  {
    timer_set_oc_value(TIM1, TIM_OC1, duty_value_from_percentage(duty_percentage));

    // sys_timer_create(&t1, 200, handle_timer, NULL);
  }
}

int main()
{
  uint32_t start_duty_percentage = 10;

  rcc_setup();
  sys_timers_init();
  systick_run();

  gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, 
    GPIO8 | GPIO9);

  rcc_periph_clock_enable(RCC_TIM1);
  
  timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1, TIM_CR1_DIR_UP);
  timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
  timer_enable_oc_output(TIM1, TIM_OC1);
  timer_enable_break_main_output(TIM1);
  timer_set_period(TIM1, 3600);
  timer_set_oc_value(TIM1, TIM_OC1, duty_value_from_percentage(100));
  timer_enable_counter(TIM1); 

  sys_timer_create(&t1, 1000, handle_timer, NULL);

  while(1)
  {

  }
}