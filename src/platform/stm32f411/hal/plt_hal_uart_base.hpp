#pragma once

#include<stdint.h>

namespace platform::hal::uart
{
  struct Pinout 
  {
    int32_t port;
    int32_t rx_pin;
    int32_t tx_pin;
  };

  constexpr int32_t INVALID_PORT = -1;
  constexpr int32_t INVALID_PIN = -1;
  constexpr int32_t INVALID_MODE = -1;
  constexpr int32_t INVALID_BAUDRATE = -1;
  constexpr int32_t INVALID_PARITY = -1;
  constexpr int32_t INVALID_DATABITS = -1;
  constexpr int32_t INVALID_STOPBITS = -1;
  constexpr int32_t INVALID_FLOW_CONTROL = -1;
}
