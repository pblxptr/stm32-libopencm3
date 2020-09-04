#pragma once

#include <stdint.h>
#include <string_view>

namespace drivers
{
  enum class Esp8266WlanMode { Client, AccessPoint, Both };
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

  class Esp8266Wlan
  {
  public:
    Esp8266Wlan(const Esp8266WlanHwCfg& hw_cfg);
    //Driver
    void init();
    void connect_ap(std::string_view ssid, std::string_view password);
    void set_mode(Esp8266WlanMode mode);

    private:  
      const Esp8266WlanHwCfg& hw_cfg_;
  };
}