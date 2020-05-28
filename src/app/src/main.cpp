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

using namespace utils::containers;

using drivers::Led;
using os::timer::Timer;

static Timer t;
static Led l;


void callback()
{
  l.toggle();

  os::timer::create(&t, 1000, callback);
}

int main()
{
  rcc_setup();

  os::core::init();
  os::core::run();

  l = Led{GPIOA, GPIO12, Led::ActiveOn::LOW};
  l.set_state(Led::State::ON);

  os::timer::create(&t, 1000, callback);

  while(1)
  {

  }
}