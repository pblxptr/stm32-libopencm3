#pragma once

#include <drivers/uart.hpp>
#include <iostream>
#include <fmt/core.h>

namespace {
  using namespace drivers::uart;
}

namespace platform::hal::uart
{
  inline void init()
  {
    platform::hal::uart::init();
  }

  template<class TConfig>
  UartDriver* setup()
  {
    // return platform::hal::uart::setup<TConfig>();
    return nullptr;
  }
  
  inline void receive(UartDriver* driver, uint8_t* buffer, size_t sz) 
  {
    // platform::hal::uart::receive(driver, buffer, sz);
  }

  inline void send(UartDriver* driver, uint8_t* buffer, size_t sz)
  {
    fmt::print("[UART-{}]: TX: {} -> ", driver->uart_id, sz);

    for (size_t i = 0; i < sz; i++)
    {
      fmt::print("{0:x} ", buffer[i]);
    }

    fmt::print(" | ");

    for (size_t i = 0; i < sz; i++)
    {
      if (buffer[i] == '\r' || buffer[i] == '\n')
        continue;
      fmt::print("{0}", (char)buffer[i]);
    }

    fmt::print("\n");
  }
}