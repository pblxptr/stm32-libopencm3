#include <drivers/gpio.hpp>
#include <hal/gpio.hpp>
#include <drivers/uart.hpp>
#include <hal/uart.hpp>
#include <platform/config.hpp>
#include <platform/peripherals.hpp>
#include <algorithm>
#include <string_view>

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))

volatile int x = 10;

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

int main()
{
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

  hal::gpio::init();
  blue_led_driver = hal::gpio::setup<decltype(blue_led_config)>();
  red_led1_driver = hal::gpio::setup<decltype(red_led1_config)>();
  red_led2_driver = hal::gpio::setup<decltype(red_led2_config)>();
  red_led3_driver = hal::gpio::setup<decltype(red_led3_config)>();

  hal::gpio::set(blue_led_driver);
  hal::gpio::set(red_led1_driver);
  hal::gpio::set(red_led2_driver);
  hal::gpio::set(red_led3_driver);

  //UAR
  constexpr auto serial1_config = drivers::uart::UartDriverConfig<
    platform::config::SERIAL1,
    drivers::uart::Mode::RX_TX,
    drivers::uart::Baudrate::B_9600,
    drivers::uart::DataBits::D_8,
    drivers::uart::StopBits::S_1,
    drivers::uart::Parity::NONE,
    drivers::uart::FlowControl::NONE
  >{};



  // //Init & setup
  hal::uart::init();
  driver = hal::uart::setup<decltype(serial1_config)>();
  // driver->rx_completed_cb = rx_completed;
  // driver->rx_end_cb = rx_ended;
  driver->tx_completed_cb = tx_completed;

  //Receive
  // uint8_t buffer[64];
  // const size_t buffer_size = ARRAY_LEN(buffer);
  // hal::uart::receive(driver, buffer, buffer_size);

  //Send
  const std::string_view msg = "Siema to jestem ja\r\n";
  uint8_t out_buffer[64]{0};
  constexpr size_t out_buffer_size = sizeof(out_buffer);
  std::copy(msg.begin(), msg.end(), out_buffer);
  hal::uart::send(driver, out_buffer, out_buffer_size);

  while(1)
  {
    if (x == 20)
    {
      x = 10;
    }
  }
}