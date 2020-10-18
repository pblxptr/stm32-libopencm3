#include <drivers/gpio.hpp>
#include <hal/gpio.hpp>
#include <drivers/uart.hpp>
#include <hal/uart.hpp>
#include <platform/config.hpp>
#include <platform/peripherals.hpp>
#include <algorithm>
#include <string_view>
#include <console_print.hpp>

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))

volatile int x = 10;

drivers::gpio::GpioDriver* blue_led_driver{nullptr};
drivers::gpio::GpioDriver* red_led1_driver{nullptr};
drivers::gpio::GpioDriver* red_led2_driver{nullptr};
drivers::gpio::GpioDriver* red_led3_driver{nullptr};

volatile bool busy{false};

drivers::uart::UartDriver* driver{nullptr};

void rx_completed([[maybe_unused]]drivers::uart::UartDriver* driver)
{
  hal::gpio::toggle(red_led1_driver); //when tc
}

void rx_ended([[maybe_unused]]drivers::uart::UartDriver* driver)
{
  hal::gpio::toggle(red_led2_driver); //when idle
}

void tx_completed([[maybe_unused]]drivers::uart::UartDriver* driver)
{
  hal::gpio::toggle(red_led3_driver); //when single character is received

}

namespace console = utils::debug::console;

int main()
{
  // //Init & setup
  hal::gpio::init();
  hal::uart::init();

  constexpr auto blue_led_config = drivers::gpio::GpioDriverConfig<
    platform::config::BLUE_LED_GPIO,
    drivers::gpio::Mode::OUTPUT,
    drivers::gpio::PullUpDown::PULLUP
  >{};

  constexpr auto red_led1_config = drivers::gpio::GpioDriverConfig<
    platform::config::RED_LED1_GPIO,
    drivers::gpio::Mode::OUTPUT,
    drivers::gpio::PullUpDown::PULLUP
  >{};

  constexpr auto red_led2_config = drivers::gpio::GpioDriverConfig<
    platform::config::RED_LED2_GPIO,
    drivers::gpio::Mode::OUTPUT,
    drivers::gpio::PullUpDown::PULLUP
  >{};

  constexpr auto red_led3_config = drivers::gpio::GpioDriverConfig<
    platform::config::RED_LED3_GPIO,
    drivers::gpio::Mode::OUTPUT,
    drivers::gpio::PullUpDown::PULLUP
  >{};

  blue_led_driver = hal::gpio::setup<decltype(blue_led_config)>();
  red_led1_driver = hal::gpio::setup<decltype(red_led1_config)>();
  red_led2_driver = hal::gpio::setup<decltype(red_led2_config)>();
  red_led3_driver = hal::gpio::setup<decltype(red_led3_config)>();

  hal::gpio::set(blue_led_driver);
  hal::gpio::set(red_led1_driver);
  hal::gpio::set(red_led2_driver);
  hal::gpio::set(red_led3_driver);

  //Setup Esp8266 uart driver
  constexpr auto serial1_config = drivers::uart::UartDriverConfig<
    platform::config::SERIAL1,
    drivers::uart::Mode::RX_TX,
    drivers::uart::Baudrate::B_9600,
    drivers::uart::DataBits::D_8,
    drivers::uart::StopBits::S_1,
    drivers::uart::Parity::NONE,
    drivers::uart::FlowControl::NONE
  >{};

  //Setup console
  constexpr auto console_config = drivers::uart::UartDriverConfig<
    platform::config::CONSOLE,
    drivers::uart::Mode::RX_TX,
    drivers::uart::Baudrate::B_9600,
    drivers::uart::DataBits::D_8,
    drivers::uart::StopBits::S_1,
    drivers::uart::Parity::NONE,
    drivers::uart::FlowControl::NONE
  >{};

  auto console_driver = hal::uart::setup<decltype(console_config)>();
  console::set_uart_driver(console_driver);

  while(1)
  {

    if (x == 20)
    {

    }
  }
}