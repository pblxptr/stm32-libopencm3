#pragma once

#include<plt_hal_uart.hpp>
#include<plt_hal_uart_t.hpp>
#include<drivers/uart.hpp>

#include <cstddef>

namespace {
  using namespace drivers::uart;
}

namespace platform::hal::uart
{
  void init();
  void setup(UartDriver&, const UartConfig&);
  void receive_poll(UartDriver&, Buffer_ptr_t, size_t);
}