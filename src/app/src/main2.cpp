#include <drivers/gpio.hpp>
#include <hal/gpio.hpp>
#include <drivers/uart.hpp>
#include <hal/uart.hpp>
#include <platform/config.hpp>
#include <platform/peripherals.hpp>


#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))

volatile int x = 10;


drivers::uart::UartDriver* driver = nullptr;
void rx_completed([[maybe_unused]]drivers::uart::UartDriver* driver)
{
  [[maybe_unused]] int x = 10;
}

void rx_ended([[maybe_unused]]drivers::uart::UartDriver* driver)
{
  [[maybe_unused]] int x = 10;
}

int main()
{
  constexpr auto blue_led_config = drivers::gpio::GpioDriverConfig<
    platform::config::BLUE_LED_GPIO,
    drivers::gpio::Mode::OUTPUT,
    drivers::gpio::PullUpDown::PULLUP
  >{};

  hal::gpio::init();
  auto led_driver = hal::gpio::setup<decltype(blue_led_config)>();

  //UART
  constexpr auto serial1_config = drivers::uart::UartDriverConfig<
    platform::config::SERIAL1,
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
  driver = hal::uart::setup<decltype(serial1_config)>();
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