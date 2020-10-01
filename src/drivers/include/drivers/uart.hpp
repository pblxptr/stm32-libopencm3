#pragma once

#include <stdint.h>

namespace drivers::uart
{
  enum class Mode : uint8_t { RX, TX, RX_TX };
  enum class Baudrate : uint8_t { B_9600, B_11200 };
  enum class DataBits : uint8_t { D_8, D_9 };
  enum class StopBits : uint8_t { S_1 };
  enum class Partiy : uint8_t { EVEN, ODD, NONE };
  enum class FlowControl : uint8_t { RTS, CTS, RTS_CTS, NONE };

  struct UartConfig 
  {
    Mode mode;
    Baudrate baudrate;
    DataBits data_bits;
    StopBits stop_bits;
    Partiy partiy;
    FlowControl flow_control;
  };

  struct UartDriver 
  {
    uint32_t id;
  };
}