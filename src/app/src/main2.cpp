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

  //UART
  constexpr auto serial1_id = platform::peripherals::get_uart_config<platform::config::SERIAL1>();
  constexpr auto uart_config = drivers::uart::UartConfig{
    drivers::uart::Mode::RX_TX,
    drivers::uart::Baudrate::B_9600,
    drivers::uart::DataBits::D_8,
    drivers::uart::StopBits::S_1,
    drivers::uart::Parity::NONE,
    drivers::uart::FlowControl::NONE
  };
  auto uart_driver = drivers::uart::UartDriver{
    serial1_id
  };
  hal::uart::init();
  hal::uart::setup(uart_driver, uart_config);
}

#else 

void rx_completed([[maybe_unused]]drivers::uart::UartDriver2* driver)
{

}

void rx_ended([[maybe_unused]]drivers::uart::UartDriver2* driver)
{

}



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
  // constexpr auto serial1_id = platform::peripherals::get_uart_config<platform::config::SERIAL1>();
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
  const size_t buffer_size = sizeof(buffer) / sizeof(buffer[0]);

  //Init & setup
  hal::uart::init();
  auto driver = hal::uart::setup<decltype(serial1_config)>();
  driver->rx_completed_cb = rx_completed;
  driver->rx_end_cb = rx_ended;
  
  hal::uart::receive(driver, buffer_size);

  //Receive

  while(1)
  {

  }
}

#endif