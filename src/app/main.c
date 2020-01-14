#include <libopencm3/stm32/rcc.h>


int main()
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  return 1;
}