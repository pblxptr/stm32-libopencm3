extern "C" {
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
}

#include <Os.hpp>
#include <Timer.hpp>
#include <List.hpp>
#include <Led.hpp>
#include <Gpio.hpp>

#define FAN_GPIO GPIOA
#define FAN_PIN  GPIO8


static void rcc_setup()
{
  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}

using utils::containers::List_t;
using drivers::Led;
using drivers::Gpio;
using os::timer::TimerHandle;


static Led fan_led;
static TimerHandle fan_timer;
static Gpio fan_gpio;


void fan_timer_callback()
{
  os::timer::create(&fan_timer, 5000, fan_timer_callback);

  fan_led.toggle();
  fan_gpio.toggle();

}

int main()
{
  rcc_setup();

  os::core::init();
  os::core::run();

  fan_led = Led{GPIOA, GPIO12, Led::ActiveOn::LOW};
  fan_gpio = Gpio{FAN_GPIO, FAN_PIN};

  os::timer::create(&fan_timer, 5000, fan_timer_callback);
  

  while(1)
  {

  }
}