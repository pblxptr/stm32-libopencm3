#include <devices/esp8266wlan.hpp>
#include <devices/esp8266commands.hpp>
#include <hal/uart.hpp>
#include <console_print.hpp>
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

  bool Esp8266Wlan::set_mode(const Mode& mode)
  {
    console::print("[ESP8266] set_mode.\r\n");
    
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
    while(!response_ready); 

    console::print("Response ready.\n");

    //Find if command was sent back from the device ECHO MODE
    auto cmdIter = find_in_rb(rx_rb_, command.command());
    if (cmdIter == rx_rb_.end())
      return false;

    //Remove command from buffer
    std::fill_n(cmdIter, command.command().size(), '\0');

    if (auto okIter = find_in_rb(rx_rb_, operation_succeed); okIter != rx_rb_.end())
    {
      console::print("Operation succeeded.\n");
      std::fill_n(okIter, operation_succeed.size(), '\0');
      return true;
    }
    else if (auto errorIter = find_in_rb(rx_rb_, operation_failed); errorIter != rx_rb_.end())
    {
      console::print("Operation failed.\n");
      std::fill_n(okIter, operation_failed.size(), '\0');
      return false;
    }

    return false;
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