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
  UartDriver2* setup()
  {
    return platform::hal::uart::setup<TConfig>();
  }
  
  inline void receive(UartDriver2* driver, uint8_t* buffer, size_t sz) 
  {
    platform::hal::uart::receive(driver, buffer, sz);
  }
}