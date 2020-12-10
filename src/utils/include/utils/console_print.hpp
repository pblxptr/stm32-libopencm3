#pragma once

#include <hal/uart.hpp>
#include <drivers/uart.hpp>

#include <utils/ring_buffer.hpp>
#include <string_view>

namespace utils::debug::console
{
  void set_uart_driver(drivers::uart::UartDriver*);
  void print(const std::string_view);
  void print(const uint8_t*, size_t);
  void print(utils::containers::RingBuffer&, size_t);
  void task();
}