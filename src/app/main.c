#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <led.h>
#include <target.h>

int main()
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();
  rcc_periph_clock_enable(RCC_GPIOA);
  
  // gpio_set_mode(FAULT_LED_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, FAULT_LED_PIN);
  // gpio_set(FAULT_LED_PORT, FAULT_LED_PIN);

  led_t fault_led;
  fault_led.gpiox = FAULT_LED_PORT;
  fault_led.pin_mask = FAULT_LED_PIN;
  fault_led.active_on = FAULT_LED_ACTIVE_ON;

  led_init(&fault_led);

  while(1)
  {


  }
}