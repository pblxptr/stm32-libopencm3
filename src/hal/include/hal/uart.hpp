#pragma once

#include<drivers/uart.hpp>
#include<platform/hal/uart.hpp>

#include<stdint.h>

namespace {
  using namespace drivers::uart;
}

namespace hal::uart
{
  void init();

  template<class TConfig>
  UartDriver2* setup()
  {
    return platform::hal::uart::setup<TConfig>();
  }
  
  inline void receive(UartDriver2* driver, size_t sz) 
  {
    uint8_t buff[100];
    platform::hal::uart::receive(driver, buff, sz);
  }
}