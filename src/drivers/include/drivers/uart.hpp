#pragma once

#include <stdint.h>

namespace drivers::uart
{
  enum class Mode : uint8_t { RX, TX, RX_TX };
  enum class Baudrate : uint8_t { B_9600, B_11200 };
  enum class DataBits : uint8_t { D_8, D_9 };
  enum class StopBits : uint8_t { S_1 };
  enum class Parity : uint8_t { EVEN, ODD, NONE };
  enum class FlowControl : uint8_t { RTS, CTS, RTS_CTS, NONE };

  using Buffer_ptr_t = uint8_t*;

  struct UartConfig 
  {
    Mode mode;
    Baudrate baudrate;
    DataBits data_bits;
    StopBits stop_bits;
    Parity partiy;
    FlowControl flow_control;
  };

  struct UartDriver 
  {
    using RxData_t = uint8_t;

    uint32_t id;
  };

  //Template version
  template<
    Mode _mode,
    Baudrate _baudrate,
    DataBits _databits,
    StopBits _stopbits,
    Parity _parity,
    FlowControl _flow_control
  >
  struct StaticUartConfig 
  {
    static constexpr Mode mode = _mode;
    static constexpr Baudrate baudrate = _baudrate;
    static constexpr DataBits databits = _databits;
    static constexpr StopBits stopbits = _stopbits;
    static constexpr Parity parity = _parity;
    static constexpr FlowControl flow_control = _flow_control;
  };

  template<
    uint32_t _uart_id
  >
  struct StaticUartDriver
  {
    static constexpr uint32_t uart_id = _uart_id;
  };
}