#pragma once

#include <hal/uart.hpp>
#include <drivers/uart.hpp>

#include <string_view>

namespace utils::debug::console
{
  void set_uart_driver(drivers::uart::UartDriver*);
  void print(const std::string_view);
}