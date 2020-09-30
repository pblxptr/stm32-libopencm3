#pragma once

#include <stdint.h>
#include <string_view>
#include <functional>

/**
 * TODO:
 *  - Blocking connect to AP 
 *  - Blocking connect to server.
 *  - Blocking accept connection
 * 
 */

namespace drivers
{
  static constexpr uint8_t ESP8266WLAN_MAX_CONNECTIONS = 4;
  static constexpr size_t ESP8266_DATA_BUFFER_SIZE = 64;

  enum class StatusCode : int32_t { SUCCESS = 0, FAILED = -1 };  
  enum class Esp8266WlanMode { Client, AccessPoint, Both };

  using Esp8266WlanConnectionId_t = int32_t;
  using CompletitionHandler_t = void(*)(const StatusCode);

  struct Esp8266WlanHwCfg
  {
    uint32_t dma_id;
    uint32_t dma_rx_channel_id;
    uint32_t dma_rx_nvic_irq;
    uint32_t dma_tx_channel_id;
    uint32_t dma_tx_nvic_channel_id;
    uint32_t usart_id;
    uint32_t usart_dr_addr;
    uint32_t usart_nvic_irq;
  };


  struct Esp8266WlanConnection 
  {
    Esp8266WlanConnectionId_t conn_id;
    uint8_t* receive_buff;
    uint8_t* send_buff;
    size_t receive_size;
    size_t send_size;
    CompletitionHandler_t send_handler;
    CompletitionHandler_t receive_handler;
    bool is_active;
  };

  class Esp8266Wlan
  {
  public:

    
    Esp8266Wlan(const Esp8266WlanHwCfg& hw_cfg);
    //Driver
    void init();
    void connect_ap(const std::string_view ssid, const std::string_view password);
    void set_mode(Esp8266WlanMode mode);

    //Api
    Esp8266WlanConnectionId_t connect(const std::string_view addr, uint16_t port);
    StatusCode disconnect(const Esp8266WlanConnectionId_t);
    StatusCode async_receive(const Esp8266WlanConnectionId_t conn_id, uint8_t* buff, const size_t size, CompletitionHandler_t handler);
    StatusCode async_send(const Esp8266WlanConnectionId_t conn_id, uint8_t* buff, const size_t size, CompletitionHandler_t handler);

    private:  
      const Esp8266WlanHwCfg& hw_cfg_;
      Esp8266WlanConnection connections_[ESP8266WLAN_MAX_CONNECTIONS];
      uint8_t receive_buffer[ESP8266_DATA_BUFFER_SIZE];
      
  };
}