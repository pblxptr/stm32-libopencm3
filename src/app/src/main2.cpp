#include <drivers/gpio.hpp>
#include <hal/gpio.hpp>
#include <drivers/uart.hpp>
#include <hal/uart.hpp>
#include <platform/config.hpp>
#include <platform/peripherals.hpp>


// #define use_static

#ifndef use_static
int main()
{
  //GPIO
  constexpr auto pinout1 = platform::peripherals::get_gpio_config<platform::config::LED_GPIO>();
  [[maybe_unused]]constexpr auto gpio1 = drivers::gpio::GpioDriver{
    pinout1,
    drivers::gpio::Mode::OUTPUT,
    drivers::gpio::PullUpDown::PULLUP
  };

  hal::gpio::init();
  hal::gpio::setup(gpio1);

  hal::gpio::set(gpio1);
  hal::gpio::clear(gpio1);

  //USART
  constexpr auto serial1_id = platform::peripherals::get_uart_config<platform::config::SERIAL1>();
}

#else 

int main()
{
  // //Template
  constexpr auto pinout1 = platform::peripherals::get_gpio_config<platform::config::LED_GPIO>();
  constexpr auto gpio1 = drivers::gpio::StaticGpioDriver<
    pinout1.port, 
    pinout1.pin,
    drivers::gpio::Mode::OUTPUT,
    drivers::gpio::PullUpDown::PULLUP
  >{};
  
  hal::gpio::init();
  hal::gpio::setup_t<decltype(gpio1)>();
  
  hal::gpio::set_t<decltype(gpio1)>();
  hal::gpio::clear_t<decltype(gpio1)>();

  while(1)
  {

  }
}

#endif