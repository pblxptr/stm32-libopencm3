#pragma once

#include <drivers/gpio.hpp>
#include <plt_peripherals_gpio.hpp>
#include <plt_peripheraps_uart.hpp>
#include <plt_hal_gpio.hpp>

namespace platform::peripherals
{
  // template<int GPIO_ID>
  // constexpr drivers::gpio::HwGpioConfig get_gpio_config()
  // {
  //   static_assert(GPIO_ID < platform::peripherals::gpio::gpios_num(), "Invalid gpio selected.");

  //   constexpr auto gpios = platform::peripherals::gpio::gpios();

  //   return gpios[GPIO_ID];
  // }

  // template<int UART_ID>
  // constexpr uint32_t get_uart_config()
  // {
  //   // constexpr auto uarts = platform::peripherals::uart::uarts();

  //   // static_assert(UART_ID < platform::peripherals::uart::uarts_num(), "Invalid uart selected.");

  //   // return uarts[UART_ID];
  // }
}