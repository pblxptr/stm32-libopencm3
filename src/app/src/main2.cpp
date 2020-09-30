#include <gpio.hpp>
#include <platform.hpp>

int main()
{
  [[maybe_unused]] auto gpio = drivers::gpio::Gpio{
    platform::gpio::get_cfg<platform::config::LED_GPIO>()
  };
}