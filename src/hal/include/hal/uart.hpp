#pragma once

#include<drivers/uart.hpp>
#include<platform/hal/uart.hpp>

#include<stdint.h>

namespace {
  using namespace drivers::uart;
}

namespace hal::uart
{
  inline void init()
  {
    platform::hal::uart::init();
  }

  template<class TConfig>
  UartDriver* setup()
  {
    return platform::hal::uart::setup<TConfig>();
  }
  
  inline void receive(UartDriver* driver, uint8_t* buffer, size_t sz) 
  {
    platform::hal::uart::receive(driver, buffer, sz);
  }

  inline void send(UartDriver* driver, uint8_t* buffer, size_t sz)
  {
    platform::hal::uart::send(driver, buffer, sz);
  }
}