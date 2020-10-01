#pragma once

#include <drivers/gpio.hpp>
#include <plt_peripherals_gpio.hpp>
#include <plt_peripheraps_uart.hpp>
#include <plt_hal_gpio.hpp>

namespace platform::peripherals
{
  template<int GPIO_ID>
  constexpr drivers::gpio::Pinout get_gpio_config()
  {
    static_assert(GPIO_ID < sizeof(platform::peripherals::gpio::gpios) / sizeof(drivers::gpio::Pinout), "Inavlid GPIO selecected.");

    return platform::peripherals::gpio::gpios[GPIO_ID];
  }

  template<int UART_ID>
  constexpr uint32_t get_uart_config()
  {
    static_assert(UART_ID < sizeof(platform::peripherals::uart::usarts) / sizeof(platform::peripherals::uart::usarts[0]), "Inavlid GPIO selecected.");

    return platform::peripherals::uart::usarts[UART_ID];
  }
}