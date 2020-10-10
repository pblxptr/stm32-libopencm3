#include <drivers/gpio.hpp>
#include <hal/gpio.hpp>
#include <drivers/uart.hpp>
#include <hal/uart.hpp>
#include <platform/config.hpp>
#include <platform/peripherals.hpp>


#define use_static

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
}

#else 

void rx_completed([[maybe_unused]]drivers::uart::UartDriver2* driver)
{
  [[maybe_unused]] int x = 10;
}

void rx_ended([[maybe_unused]]drivers::uart::UartDriver2* driver)
{
  [[maybe_unused]] int x = 10;
}

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))

volatile int x = 10;

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

  //UART
  constexpr auto serial1_config = drivers::uart::StaticUartConfig<
    (uint32_t)USART1,
    drivers::uart::Mode::RX_TX,
    drivers::uart::Baudrate::B_9600,
    drivers::uart::DataBits::D_8,
    drivers::uart::StopBits::S_1,
    drivers::uart::Parity::NONE,
    drivers::uart::FlowControl::NONE
  >{};

  uint8_t buffer[64];
  const size_t buffer_size = ARRAY_LEN(buffer);

  // //Init & setup
  hal::uart::init();
  auto driver = hal::uart::setup<decltype(serial1_config)>();
  driver->rx_completed_cb = rx_completed;
  driver->rx_end_cb = rx_ended;
  
  hal::uart::receive(driver, buffer, buffer_size);

  while(1)
  {
    if (x == 20)
    {
      x = 10;
    }
  }
}

#endif