#pragma once

#include <stdint.h>
#include <string_view>

namespace drivers
{
  enum class Esp8266WlanMode { Client, AccessPoint, Both };
  class Esp8266Wlan
  {
  public:
    Esp8266Wlan(uint32_t usart);
    //Driver
    void init();
    void connect_ap(std::string_view ssid, std::string_view password);
    void set_mode(Esp8266WlanMode mode);

    //Api
    private:  
      uint32_t usart_;
  };
}