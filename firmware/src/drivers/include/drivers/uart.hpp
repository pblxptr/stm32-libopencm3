#pragma once

#include <stdint.h>
#include <type_traits>
#include <cstddef>
#include <chrono>
#include <os/timer.hpp>
#include <gsl/span>

namespace drivers::uart
{
  enum class Mode : uint8_t { RX, TX, RX_TX };
  enum class Baudrate : uint8_t { B_9600, B_115200 };
  enum class DataBits : uint8_t { D_8, D_9 };
  enum class StopBits : uint8_t { S_1 };
  enum class Parity : uint8_t { EVEN, ODD, NONE };
  enum class FlowControl : uint8_t { RTS, CTS, RTS_CTS, NONE };

  struct UartDriver;

  using buffer_ptr_t = uint8_t*;
  using rx_completed_t = std::add_pointer_t<void(void*)>;
  using rx_end_t = std::add_pointer_t<void(void*, const size_t)>; //TODO: Can we get rid of void*?

  using tx_completed_t = std::add_pointer_t<void(void*)>;

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
  struct UartDriverConfig 
  {
    static constexpr uint32_t uart_id = _uart_id;
    static constexpr Mode mode = _mode;
    static constexpr Baudrate baudrate = _baudrate;
    static constexpr DataBits databits = _databits;
    static constexpr StopBits stopbits = _stopbits;
    static constexpr Parity parity = _parity;
    static constexpr FlowControl flow_control = _flow_control;
  };

  enum class UartState { IDLE, ACTIVE };

  template<class Derived>
  class IUartDriver
  {
    IUartDriver() {}
    friend Derived;

    Derived& impl() { return static_cast<Derived&>(*this); }
  public:
    void set_rx_completed_callback(rx_completed_t cb)
    {
      impl().set_rx_completed_callback(cb);
    }
    void set_rx_end_callback(rx_end_t cb)
    {
      impl().set_rx_end_callback(cb);
    }
    void set_tx_completed_callback(tx_completed_t cb)
    {
      impl().set_tx_completed_callback(cb);
    }
    void set_rx_event_context(void* ctx)
    {
      impl().set_rx_event_context(ctx);
    }
    void set_tx_event_context(void* ctx)
    {
      impl().set_tx_event_context(ctx);
    }
    size_t receive(gsl::span<uint8_t> buffer, const std::chrono::milliseconds& timeout = {})
    {
      return impl().receive(buffer, timeout);
    }
    void send(gsl::span<uint8_t> buffer)
    {
      impl().send(buffer);
    }
  };

  struct UartDriver : IUartDriver<UartDriver>
  {
    uint32_t uart_id;
    //RX
    UartState rx_state;
    //RX -> events
    rx_completed_t rx_completed_cb;
    rx_end_t rx_end_cb;
    void* rx_event_ctx;
    
    //TX
    UartState tx_state;
    //TX -> events
    tx_completed_t tx_completed_cb;
    void* tx_event_ctx;

    void set_rx_completed_callback(rx_completed_t cb);
    void set_rx_end_callback(rx_end_t cb);
    void set_tx_completed_callback(tx_completed_t cb);
    void set_rx_event_context(void* ctx);
    void set_tx_event_context(void* ctx);

    size_t receive(gsl::span<uint8_t> buffer, const std::chrono::milliseconds& timeout = {});
    void send(gsl::span<uint8_t> buffer);
  };
}