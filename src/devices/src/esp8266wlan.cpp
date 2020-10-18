#include <devices/esp8266wlan.hpp>
#include <hal/uart.hpp>
#include <console_print.hpp>

using namespace drivers::uart;
using namespace devices::esp8266;
namespace console = utils::debug::console;

namespace {
  static void handle_rx_end_wrapper(void* ctx)
  {
    Esp8266Wlan* device = reinterpret_cast<Esp8266Wlan*>(ctx);
    device->handle_rx_end();
  }
}

static volatile bool sync{true};

namespace devices::esp8266
{
  Esp8266Wlan::Esp8266Wlan(UartDriver* uart)
    : uart_{uart}
    {
      uart->rx_end_cb = handle_rx_end_wrapper;
      uart->rx_event_ctx = this;

      hal::uart::receive(uart_, rx_buffer_, RX_BUFFER_SIZE);
    }

  void Esp8266Wlan::connect_to_wifi(const std::string_view uuid, const std::string_view password) {}
  
  //Handles
  void Esp8266Wlan::handle_rx_end()
  {
    sync = false;
  }

  void Esp8266Wlan::task()
  {
    if (!sync)
    {
      console::print(std::string_view{"test"});
    }

    sync = true; 
  }
}