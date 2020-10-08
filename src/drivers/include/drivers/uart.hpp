#pragma once

#include <stdint.h>
#include <type_traits>

namespace drivers::uart
{
  enum class Mode : uint8_t { RX, TX, RX_TX };
  enum class Baudrate : uint8_t { B_9600, B_11200 };
  enum class DataBits : uint8_t { D_8, D_9 };
  enum class StopBits : uint8_t { S_1 };
  enum class Parity : uint8_t { EVEN, ODD, NONE };
  enum class FlowControl : uint8_t { RTS, CTS, RTS_CTS, NONE };

  struct UartDriver2;

  using buffer_ptr_t = uint8_t*;
  using rx_completed_t = std::add_pointer_t<void(UartDriver2* ctx)>;
  using rx_end_t = std::add_pointer_t<void(UartDriver2* ctx)>;

  //Template version
  template<
    auto _uart_id,
    Mode _mode,
    Baudrate _baudrate,
    DataBits _databits,
    StopBits _stopbits,
    Parity _parity,
    FlowControl _flow_control
  >
  struct StaticUartConfig 
  {
    static constexpr uint32_t uart_id = _uart_id;
    static constexpr Mode mode = _mode;
    static constexpr Baudrate baudrate = _baudrate;
    static constexpr DataBits databits = _databits;
    static constexpr StopBits stopbits = _stopbits;
    static constexpr Parity parity = _parity;
    static constexpr FlowControl flow_control = _flow_control;
  };

  struct UartDriver2
  {
    uint32_t uart_id;
    rx_completed_t rx_completed_cb;
    rx_end_t rx_end_cb;
  };
}