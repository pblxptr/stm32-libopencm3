#pragma once

#include <drivers/uart.hpp>
#include <platform/hal/uart.hpp>

namespace hal::uart
{
  void init()
  {
    platform::hal::uart::init();
  }

  void setup(drivers::uart::UartDriver& driver, drivers::uart::UartConfig& config)
  {
    platform::hal::uart::setup(driver, config);
  }
}