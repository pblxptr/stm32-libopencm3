#pragma once

#include <string_view>
#include <stdint.h>

namespace drivers::esp8266 
{
  enum class StatusCode { FAILED = -1, SUCCESS = 0};
  enum class WlanMode { Client, AccessPoint, Both };

  using WlanConnectionId_t = int32_t;
  using CompletitionHandler_t = void(*)(const StatusCode);

  struct WlanHwCfg
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

  //Driver related
  void init(const WlanHwCfg& hw_cfg);
  void set_mode(const WlanMode& wlan_mode);
  void connect_ap(const std::string_view ssid, const std::string_view password);

  //Api
  void process();
}