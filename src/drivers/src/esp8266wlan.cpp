#include <devices/esp8266wlan.hpp>

using namespace drivers::uart;

namespace {
  
}

namespace devices::esp8266
{
  Esp8266::Esp8266(UartDriver* uart)
    : uart_{uart}
    {}

  void Esp8266::connect_to_wifi(const std::string_view uuid, const std::string_view password)
  {

  }
}