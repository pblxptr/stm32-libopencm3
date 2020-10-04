#pragma once

#include<drivers/uart.hpp>
#include<platform/hal/uart.hpp>

#include<stdint.h>

namespace hal::uart
{
  void init();
  // void setup(drivers::uart::UartDriver& driver, const drivers::uart::UartConfig& config)
  // {
  //   platform::hal::uart::setup(driver, config);
  // }

  //Template version
  template<class TUartDriver, class TConfig>
  void setup()
  {
    platform::hal::uart::setup<TUartDriver, TConfig>();
  }

  // template<class TUartDriver> 
  // void receive_poll(TUartDriver*, Buffer_ptr_t, size_t);

  template<auto uart_id> 
  void receive_poll(StaticUartDriver<uart_id>*, Buffer_ptr_t, size_t);

}