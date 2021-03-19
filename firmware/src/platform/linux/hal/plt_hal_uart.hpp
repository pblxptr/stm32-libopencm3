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

  inline void receive([[maybe_unused]] drivers::uart::UartDriver* driver, [[maybe_unused]]  uint8_t* buff, [[maybe_unused]]  const size_t sz)
  {

  }

  inline void send([[maybe_unused]] drivers::uart::UartDriver* driver, [[maybe_unused]]  uint8_t* buff, [[maybe_unused]]  const size_t sz)
  {

  }
}