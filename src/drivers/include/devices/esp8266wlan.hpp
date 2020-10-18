#pragma once

#include <drivers/uart.hpp>

#include <string_view>

namespace {
  using namespace drivers::uart;
}

namespace devices::esp8266
{
  class Esp8266
  {
    UartDriver* uart_;
  public:
    explicit Esp8266(UartDriver* uart);
    void connect_to_wifi(const std::string_view uuid, const std::string_view password);
  };
}