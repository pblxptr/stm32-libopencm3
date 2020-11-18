#include <devices/esp8266wlan.hpp>
#include <devices/esp8266commands.hpp>
#include <hal/uart.hpp>
#include <console_print.hpp>
#include <cstring>
#include <cmath>

#include <iostream>



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

  //Helpers
  bool find_in_rb(RingBuffer& rb, const std::string_view needle)
  {
    const auto head_backup = rb.head();
    size_t needle_idx = 0;

    while (rb.tail() != head_backup)
    {
      const auto data = rb.read();
      rb.write(data);

      if (data != needle[needle_idx++])
        needle_idx = 0;

      if (needle_idx == needle.size())
        return true;
    }

    return false;
  }
}

static volatile bool response_ready{false};

static size_t expected_response_size = 0;

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

  void Esp8266Wlan::set_mode(const Mode& mode)
  {
    console::print("[ESP8266] set_mode.\r\n");
    
    const auto command = CwModeCommand{mode};

    execute_blocking_operation(command);
  }

  void Esp8266Wlan::execute_blocking_operation(const CwModeCommand& command)
  {
    tx_rb_.clear();
    command.serialize(tx_rb_);
    tx_rb_.write(operation_terminator.data(), operation_terminator.size());

    hal::uart::send(uart_, tx_buffer_, tx_rb_.capacity());

    while(!response_ready); 

    const bool isOkFound = find_in_rb(rx_rb_, "OK");
    const bool isErrorFound = find_in_rb(rx_rb_, "ERROR");

    if (isOkFound)
    {
      std::cout << "[ESP8266] Ok response found.\n";
    }
    else if (isErrorFound)
    {
      std::cout << "[ESP8266] Error response found.\n";
    }
    else 
    {
      std::cout << "[ESP8266] Response not found.\n";
    }


  }

  void Esp8266Wlan::connect_wlan(const std::string_view uuid, const std::string_view password) {}
  
  //Handles
  void Esp8266Wlan::handle_rx_end(const size_t nbytes)
  {
    for (size_t i = 0; i < nbytes; i++)
    {
      rx_rb_.write(rx_buffer_[i]);
    }

    response_ready = true;
  }

  void Esp8266Wlan::task()
  {
    
  }

}