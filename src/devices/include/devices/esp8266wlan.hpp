#pragma once

#include <drivers/uart.hpp>

#include <string_view>

namespace {
  using namespace drivers::uart;
}

namespace devices::esp8266
{
  constexpr size_t RX_BUFFER_SIZE = 128;
  class Esp8266Wlan
  {
    UartDriver* uart_;
    uint8_t rx_buffer_[RX_BUFFER_SIZE];
  public:
    explicit Esp8266Wlan(UartDriver* uart);
    void connect_to_wifi(const std::string_view uuid, const std::string_view password);

    void task();

    //Handles
    void handle_rx_end();
  };
}