#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <led.h>
#include <target.h>
// #include <sys_timer.h>
#include <libopencm3/stm32/exti.h>
#include <delay.h>
#include <hd44780.h>
#include <libopencm3/stm32/i2c.h>
#include <ssd1306.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <hal/exti.h>
#include <rotary_encoder.h>
#include <stdlib.h>

static led_t fault_led;
static led_t operational_led;
static led_t status_led;
static sys_timer_t fault_led_timer;
static sys_timer_t operational_led_timer;
static sys_timer_t status_led_timer;

static void rcc_setup()
{
  //Clock setup
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}

static void i2c_setup()
{
  //Required by hd44780 
  rcc_periph_clock_enable(RCC_I2C1);
  rcc_periph_clock_enable(RCC_AFIO);

  gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, GPIO_I2C2_SCL | GPIO_I2C2_SDA);

  i2c_peripheral_disable(I2C2);
  i2c_set_clock_frequency(I2C2, I2C_CR2_FREQ_36MHZ);
  i2c_set_ccr(I2C2, 0x1e);
  i2c_set_trise(I2C2, 0x0b);
  i2c_set_own_7bit_slave_address(I2C2, 0x32);
  i2c_peripheral_enable(I2C2);
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
  i2c_setup();

  sys_timers_init();
  systick_run();


  while(1)
  {
  }
}