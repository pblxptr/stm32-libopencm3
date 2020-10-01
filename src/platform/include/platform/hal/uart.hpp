#pragma once

#include<plt_hal_uart.hpp>
#include<drivers/uart.hpp>

namespace platform::hal::uart
{
  void init();
  void setup(drivers::uart::UartDriver&, const drivers::uart::UartConfig&);
}