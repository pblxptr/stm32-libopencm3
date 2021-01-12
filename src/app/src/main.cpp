#include <algorithm>
#include <string_view>

#include <drivers/uart.hpp>
#include <drivers/gpio.hpp>
#include <hal/gpio.hpp>
#include <hal/uart.hpp>
#include <hal/dma.hpp>
#include <platform/config.hpp>
#include <utils/console_print.hpp>
#include <devices/esp8266wlan.hpp>

drivers::gpio::GpioDriver* blue_led_driver{nullptr};
drivers::gpio::GpioDriver* red_led1_driver{nullptr};
drivers::gpio::GpioDriver* red_led2_driver{nullptr};
drivers::gpio::GpioDriver* red_led3_driver{nullptr};

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
using namespace devices::esp8266;

int main()
{
  // //Init & setup
  hal::gpio::init();
  hal::uart::init();
  hal::dma::init();

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

  //Setup Esp8266
  constexpr auto esp8266_gpio_rx = drivers::gpio::GpioDriverConfig<
    platform::config::SERIAL1_GPIO_RX,
    drivers::gpio::Mode::AF,
    drivers::gpio::PullUpDown::NONE,
    7 
  >{};
  constexpr auto esp8266_gpio_tx = drivers::gpio::GpioDriverConfig<
    platform::config::SERIAL1_GPIO_TX,
    drivers::gpio::Mode::AF,
    drivers::gpio::PullUpDown::NONE,
    7
  >{};
  constexpr auto esp8266_uart_config = drivers::uart::UartDriverConfig<
    platform::config::SERIAL1,
    drivers::uart::Mode::RX_TX,
    drivers::uart::Baudrate::B_115200,
    drivers::uart::DataBits::D_8,
    drivers::uart::StopBits::S_1,
    drivers::uart::Parity::NONE,
    drivers::uart::FlowControl::NONE
  >{};
  hal::gpio::setup<decltype(esp8266_gpio_rx)>();
  hal::gpio::setup<decltype(esp8266_gpio_tx)>();
  auto esp8266_uart_driver = hal::uart::setup<decltype(esp8266_uart_config)>();

  //Setup console
  constexpr auto console_gpio_rx = drivers::gpio::GpioDriverConfig<
    platform::config::CONSOLE_GPIO_RX,
    drivers::gpio::Mode::AF,
    drivers::gpio::PullUpDown::NONE,
    7
  >{};
  constexpr auto console_gpio_tx = drivers::gpio::GpioDriverConfig<
    platform::config::CONSOLE_GPIO_TX,
    drivers::gpio::Mode::AF,
    drivers::gpio::PullUpDown::NONE,
    7
  >{};
  constexpr auto console_uart_config = drivers::uart::UartDriverConfig<
    platform::config::CONSOLE,
    drivers::uart::Mode::RX_TX,
    drivers::uart::Baudrate::B_9600,
    drivers::uart::DataBits::D_8,
    drivers::uart::StopBits::S_1,
    drivers::uart::Parity::NONE,
    drivers::uart::FlowControl::NONE
  >{};
  hal::gpio::setup<decltype(console_gpio_rx)>();
  hal::gpio::setup<decltype(console_gpio_tx)>();
  auto console_driver = hal::uart::setup<decltype(console_uart_config)>();
  console::set_uart_driver(console_driver);

  auto esp8266_wlan = Esp8266Wlan{esp8266_uart_driver};
  
  esp8266_wlan.reset();
  esp8266_wlan.set_mode(devices::esp8266::Mode::Client);

  while(1)
  {
    console::task();
    esp8266_wlan.task();
  }
}