#include <devices/esp8266wlan.hpp>
#include <devices/cwmode_command.hpp>
#include <devices/cwjap_command.hpp>
#include <devices/reset_command.hpp>
#include <hal/uart.hpp>
#include <utils/console_print.hpp>
#include <cstring>
#include <chrono>
#include <gsl/span>

using namespace drivers::uart;
using namespace devices::esp8266;
using namespace std::literals;

namespace console = utils::debug::console;

namespace {
  #define ARRAY_LEN(x) ((sizeof(x)/sizeof(x[0])))

  static constexpr std::string_view operation_succeed{"OK"};
  static constexpr std::string_view operation_failed{"ERROR"};
  static constexpr std::string_view operation_terminator{"\r\n"};
  static constexpr std::chrono::milliseconds receive_timeout = std::chrono::milliseconds{ 500 };

   //Handle from ISR
  // static void handle_rx_end_wrapper(void* ctx, const size_t nbytes)
  // {
  //   Esp8266Wlan* device = reinterpret_cast<Esp8266Wlan*>(ctx);
  //   device->handle_rx_end(nbytes);
  // }

  // static void handle_tx_end_wrapper(void* ctx)
  // {
  //   Esp8266Wlan* device = reinterpret_cast<Esp8266Wlan*>(ctx);
  //   device->handle_tx_end();
  // }

  static auto find_in_rb(const RingBuffer& rb, std::string_view needle)
  {
    return rb.find(reinterpret_cast<const uint8_t*>(needle.data()), needle.size());
  }

  static bool remove_from_buffer(const RingBuffer& rb, std::string_view payload)
  {
    auto iter = find_in_rb(rb, payload);

    if (iter == rb.end())
    {
      return false;
    }

    std::fill_n(iter, operation_succeed.size(), '\0');
    return true;
  }
}

static volatile size_t rx_size = 0;

namespace devices::esp8266
{
  template<class T>
  Esp8266Wlan<T>::Esp8266Wlan(IUartDriver<T>* uart)
    : uart_{uart}
    , rx_rb_{rx_buffer_, RX_BUFFER_SIZE}
    , tx_rb_{tx_buffer_, TX_BUFFER_SIZE}
    {
      uart->set_rx_event_context(this);
      uart->set_rx_end_callback([](void* ctx, const size_t nbytes) { reinterpret_cast<Esp8266Wlan*>(ctx)->handle_rx_end(nbytes); });

      uart->set_tx_event_context(this);
      uart->set_tx_completed_callback([](void* ctx) { reinterpret_cast<Esp8266Wlan*>(ctx)->handle_tx_end(); });

      std::fill_n(rx_buffer_, RX_BUFFER_SIZE, '\0');
      std::fill_n(tx_buffer_, TX_BUFFER_SIZE, '\0');
    }

  template<class T>
  bool Esp8266Wlan<T>::reset()
  {
    trace(1, "[ESP8266] Esp8266Wlan::reset()\r\n");
    
    const auto command = ResetCommand{};

    return execute_blocking_operation(command);
  }

  template<class T>
  bool Esp8266Wlan<T>::set_mode(const Mode& mode)
  {
    trace(1, "[ESP8266] Esp8266Wlan::set_mode()\r\n");
    
    const auto command = CwModeCommand{mode};

    return execute_blocking_operation(command);
  }

  template<class T>
  bool Esp8266Wlan<T>::connect_wlan(const std::string_view uuid, const std::string_view password) 
  {
    trace(1, "[ESP8266] Esp8266Wlan::connect_wlan()\r\n");

    const auto command = CwJapCommand{uuid, password};

    return execute_blocking_operation(command);
  }

  template<class T>
  template<class TCommand>
  bool Esp8266Wlan<T>::execute_blocking_operation(const TCommand& command)
  {
    //Serialize command
    tx_rb_.clear();
    command.serialize(tx_rb_);
    tx_rb_.write(operation_terminator.data(), operation_terminator.size());

    //Send command
    uart_->send(gsl::span<uint8_t>{tx_buffer_, tx_rb_.capacity()});
    uart_->receive(gsl::span<uint8_t>{rx_buffer_, RX_BUFFER_SIZE}, receive_timeout);

    trace(3, "[ESP8266] Response ready.\r\n");

    // Check echo command
    if (!remove_from_buffer(rx_rb_, command.command()))
    {
      trace_error("[ESP8266] Command echo not found in buffer.\r\n");
      return false;
    }

    if (remove_from_buffer(rx_rb_, operation_succeed)) 
    {
      trace(3, "[ESP8266] Operation succeeded.\r\n");
      
      return true;
    }
    else if (remove_from_buffer(rx_rb_, operation_failed))
    {
      trace_error("[ESP8266] Operation failed.\r\n");

      return false;
    }
    else 
    {
      trace_error("[ESP8266] Neither success nor faild response found in buffer.\r\n");
      
      return false;
    }
    return false;
  }
  
  template<class T>
  void Esp8266Wlan<T>::task()
  {
    
  }


  //Handles
  template<class T>
  void Esp8266Wlan<T>::handle_rx_end(const size_t nbytes)
  {
    const size_t start_idx = RX_BUFFER_SIZE - nbytes;
    const size_t bytes_count = RX_BUFFER_SIZE - nbytes;

    rx_size += RX_BUFFER_SIZE - nbytes;
    for (size_t i = start_idx; i < bytes_count; ++i)
    {
      rx_rb_.write(rx_buffer_[i]);
    }
  }

  template<class T>
  void Esp8266Wlan<T>::handle_tx_end()
  {

  }

template Esp8266Wlan<UartDriver>::Esp8266Wlan(IUartDriver<UartDriver>*);
template bool Esp8266Wlan<UartDriver>::reset();
template bool Esp8266Wlan<UartDriver>::set_mode(const Mode&);
template bool Esp8266Wlan<UartDriver>::connect_wlan(const std::string_view, const std::string_view);
template void Esp8266Wlan<UartDriver>::task();
}