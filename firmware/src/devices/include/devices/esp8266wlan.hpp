#pragma once

#include <drivers/uart.hpp>
#include <utils/ring_buffer.hpp>

#include <string_view>

namespace {
  using namespace drivers::uart;
  using namespace utils::containers;
}

namespace devices::esp8266
{
  constexpr size_t RX_BUFFER_SIZE = 128;
  constexpr size_t TX_BUFFER_SIZE = 128;

  enum class Mode : uint16_t { Client, AccessPoint };
  
  template<class TUart>
  class Esp8266Wlan
  {
  public: //TODO: Temporary
    IUartDriver<TUart>* uart_;
    //RX
    uint8_t rx_buffer_[RX_BUFFER_SIZE];
    RingBuffer rx_rb_;
    //TX
    uint8_t tx_buffer_[TX_BUFFER_SIZE];
    RingBuffer tx_rb_;
  public:
    explicit Esp8266Wlan(IUartDriver<TUart>* uart);

    //Configuration methods
    bool reset();
    bool set_mode(const Mode&);
    bool connect_wlan(const std::string_view uuid, const std::string_view password);

    void task();

    //Handles -> called from interrupts
    void handle_rx_end(const size_t);
    void handle_tx_end();
    
  private:
    template<class T>
    bool execute_blocking_operation(const T&);
  };
}