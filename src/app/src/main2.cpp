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
  constexpr auto serial1_id = platform::peripherals::get_uart_config<platform::config::SERIAL1>();
  constexpr auto serial1_config = drivers::uart::StaticUartConfig<
    drivers::uart::Mode::RX_TX,
    drivers::uart::Baudrate::B_9600,
    drivers::uart::DataBits::D_8,
    drivers::uart::StopBits::S_1,
    drivers::uart::Parity::NONE,
    drivers::uart::FlowControl::NONE
  >{};
  auto serial1_driver = drivers::uart::StaticUartDriver<
    serial1_id
  >{};

  constexpr auto serial2_id = platform::peripherals::get_uart_config<platform::config::SERIAL2>();
  constexpr auto serial2_config = drivers::uart::StaticUartConfig<
    drivers::uart::Mode::RX_TX,
    drivers::uart::Baudrate::B_9600,
    drivers::uart::DataBits::D_8,
    drivers::uart::StopBits::S_1,
    drivers::uart::Parity::NONE,
    drivers::uart::FlowControl::NONE
  >{};
  auto serial2_driver = drivers::uart::StaticUartDriver<
    serial2_id
  >{};

  //Init & setup
  hal::uart::init();
  hal::uart::setup<decltype(serial1_driver), decltype(serial1_config)>();
  hal::uart::setup<decltype(serial2_driver), decltype(serial2_config)>();

  //Receive
  using Serial1type = decltype(serial1_driver);
  uint8_t buffer[64];
  constexpr size_t buff_size = sizeof(buffer);
  hal::uart::receive_poll<Serial1type::uart_id>(&serial1_driver, buffer, buff_size);

  while(1)
  {

  }
}

#endif