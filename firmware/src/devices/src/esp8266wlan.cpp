#include <devices/esp8266wlan.hpp>
#include <devices/esp8266commands.hpp>
#include <hal/uart.hpp>
#include <utils/console_print.hpp>
#include <cstring>

using namespace drivers::uart;
using namespace devices::esp8266;
using namespace std::literals;

namespace console = utils::debug::console;

namespace {
  #define ARRAY_LEN(x) ((sizeof(x)/sizeof(x[0])))

  static constexpr std::string_view operation_succeed{"OK"};
  static constexpr std::string_view operation_failed{"ERROR"};
  static constexpr std::string_view operation_terminator{"\r\n"};

   //Handle from ISR
  static void handle_rx_end_wrapper(void* ctx, const size_t nbytes)
  {
    Esp8266Wlan* device = reinterpret_cast<Esp8266Wlan*>(ctx);
    device->handle_rx_end(nbytes);
  }

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
  Esp8266Wlan::Esp8266Wlan(UartDriver* uart)
    : uart_{uart}
    , rx_rb_{rx_buffer_, RX_BUFFER_SIZE}
    , tx_rb_{tx_buffer_, TX_BUFFER_SIZE}
    {
      uart->rx_end_cb = handle_rx_end_wrapper;
      uart->rx_event_ctx = this;

      std::fill_n(rx_buffer_, RX_BUFFER_SIZE, '\0');
      std::fill_n(tx_buffer_, TX_BUFFER_SIZE, '\0');

      hal::uart::receive(uart_, rx_buffer_, RX_BUFFER_SIZE);
    }

  void Esp8266Wlan::reset()
  {

  }

  bool Esp8266Wlan::set_mode(const Mode& mode)
  {
    trace(1, "[ESP8266] Esp8266Wlan::set_mode()\r\n");
    
    const auto command = CwModeCommand{mode};

    return execute_blocking_operation(command);
  }

  bool Esp8266Wlan::execute_blocking_operation(const CwModeCommand& command)
  {
    //Serialize command
    tx_rb_.clear();
    command.serialize(tx_rb_);
    tx_rb_.write(operation_terminator.data(), operation_terminator.size());

    //Send command
    hal::uart::send(uart_, tx_buffer_, tx_rb_.capacity());

    //Wait for response
    while(rx_size < 5); 

    trace(3, "[ESP8266] Response readyyy\r\n");

    //Check echo command
    if (!remove_from_buffer(rx_rb_, command.command()))
    {
      trace_error("[ESP8266] Command echo not found in buffer.\r\n");
      return false;
    }

    if (remove_from_buffer(rx_rb_, operation_succeed)) 
    {
      trace(3, "[ESP8266] Operation succeeded\r\n");
      
      return true;
    }
    else if (remove_from_buffer(rx_rb_, operation_failed))
    {
      trace_error("[ESP8266] Operation failed\r\n");

      return false;
    }
    else 
    {
      trace_error("[ESP8266] Neither success nor faild response found in buffer.\r\n");
      
      return false;
    }
    return false;
  }

  void Esp8266Wlan::connect_wlan(const std::string_view uuid, const std::string_view password) {}
  
  //Handles
  void Esp8266Wlan::handle_rx_end(const size_t nbytes)
  {
    const size_t start_idx = RX_BUFFER_SIZE - nbytes;
    const size_t bytes_count = RX_BUFFER_SIZE - nbytes;

    rx_size += RX_BUFFER_SIZE - nbytes;
    for (size_t i = start_idx; i < bytes_count; ++i)
    {
      rx_rb_.write(rx_buffer_[i]);
    }
  }

  void Esp8266Wlan::task()
  {
    
  }
}