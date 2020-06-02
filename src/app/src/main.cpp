extern "C" {
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
}

#include <Os.hpp>
#include <Timer.hpp>
#include <List.hpp>
#include <Led.hpp>

static void rcc_setup()
{
  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}

using utils::containers::List_t;
using drivers::Led;
using os::timer::TimerHandle;

static TimerHandle t1;
static TimerHandle t2;
static TimerHandle t3;

static Led l;


void t1_cb()
{
  l.toggle();
}

void t2_cb()
{
  l.toggle();
}

void t3_cb()
{
  l.toggle();
}


int main()
{
  rcc_setup();

  os::core::init();
  os::core::run();

  l = Led{GPIOA, GPIO12, Led::ActiveOn::LOW};

  os::timer::create(&t1, 2000, t1_cb);
  os::timer::create(&t3, 8000, t3_cb);
  os::timer::create(&t2, 5000, t2_cb);
  

  while(1)
  {

  }
}