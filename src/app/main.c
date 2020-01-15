#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int main()
{
  // rcc_clock_setup_in_hse_8mhz_out_72mhz();
  // rcc_periph_clock_enable(RCC_GPIOA);
  
  // gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO11);

  // gpio_toggle(GPIOA, GPIO11);
  while(1)
  {

  }
}