#pragma once

#include <drivers/uart.hpp>
#include <ring_buffer.hpp>

#include <string_view>

namespace {
  using namespace drivers::uart;
  using namespace utils::containers;
}

namespace devices::esp8266
{
  constexpr size_t RX_BUFFER_SIZE = 256;
  constexpr size_t TX_BUFFER_SIZE = 128;

  class Esp8266Wlan
  {
    UartDriver* uart_;
    //RX
    uint8_t rx_buffer_[RX_BUFFER_SIZE];
    RingBuffer rx_rb_;
    //TX
    uint8_t tx_buffer_[TX_BUFFER_SIZE];
    RingBuffer tx_rb_;
  public:
    explicit Esp8266Wlan(UartDriver* uart);

    //Configuration methods
    void set_mode();
    void test(); //TODO: Remove after driver is done.
    void connect_wlan(const std::string_view uuid, const std::string_view password);

    //Network API

    //Task
    void task();

    //Handles -> called from interrupts
    void handle_rx_end(const size_t);
    
  };
}