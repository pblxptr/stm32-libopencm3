#pragma once

#include <drivers/uart.hpp>

#include <stdint.h>
#include <cstddef>

namespace {
  using namespace drivers::uart;
}

namespace platform::hal::uart
{ 
  inline void init()
  {

  }

  template<class TConfig>
  UartDriver* setup()
  {
    return nullptr;
  }

  inline void receive(drivers::uart::UartDriver* driver, uint8_t* buff, const size_t sz)
  {

  }

  inline void send(drivers::uart::UartDriver* driver, uint8_t* buff, const size_t sz)
  {

  }
}