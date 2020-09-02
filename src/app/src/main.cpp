extern "C" {
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>
}

#include <Os.hpp>
#include <Timer.hpp>
#include <List.hpp>
#include <Led.hpp>
#include <Gpio.hpp>
#include <uprintf.hpp>
#include <stdio.h>
#include <server.hpp>

static void rcc_setup()
{
  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}


int main()
{
  rcc_setup();

  os::core::init();
  os::core::run();

  server_init();
  server_run();

  while(true) 
  {

  }
}