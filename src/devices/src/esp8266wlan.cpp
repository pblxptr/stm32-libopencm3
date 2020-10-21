#include <devices/esp8266wlan.hpp>
#include <hal/uart.hpp>
#include <console_print.hpp>
#include <cstring>

using namespace drivers::uart;
using namespace devices::esp8266;
namespace console = utils::debug::console;

namespace {
  static void handle_rx_end_wrapper(void* ctx, const size_t nbytes)
  {
    Esp8266Wlan* device = reinterpret_cast<Esp8266Wlan*>(ctx);
    device->handle_rx_end(nbytes);
  }
}

static constexpr std::string_view operation_succeed{"OK"};
static constexpr std::string_view operation_failed{"ERROR"};

static volatile bool sync{true};
static volatile bool operation_in_progress{false};

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
    }

  void Esp8266Wlan::set_mode()
  {

    constexpr auto cmd = std::string_view{"AT+CIPSTART=1,\"TCP\",\"192.168.0.115\",5566\r\n"};
    std::copy(cmd.begin(), cmd.end(), tx_buffer_);

    hal::uart::receive(uart_, rx_buffer_, RX_BUFFER_SIZE);
    hal::uart::send(uart_, tx_buffer_, cmd.size());
    // console::print("Set mode failed.");

  }


  void Esp8266Wlan::connect_wlan(const std::string_view uuid, const std::string_view password) {}
  
  //Handles
  void Esp8266Wlan::handle_rx_end(const size_t nbytes)
  {
    sync = false; 

    for (size_t i = 0; i < nbytes; i++)
    {
      rx_rb_.write(rx_buffer_[i]);
    }


  }

  void Esp8266Wlan::task()
  {
    if (!sync)
    {
      console::print(rx_rb_, rx_rb_.capacity());
    }

    sync = true; 
  }
}