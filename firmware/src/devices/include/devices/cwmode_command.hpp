#pragma once

#include <utils/ring_buffer.hpp>
#include <devices/esp8266wlan.hpp>

namespace devices::esp8266
{
  class CwModeCommand
  {
    devices::esp8266::Mode mode_;
  public:
    static constexpr std::string_view command_name = "AT+CWMODE=";


    explicit CwModeCommand(const devices::esp8266::Mode& mode)
      : mode_{mode} {}

    constexpr std::string_view command() const 
    {
      return command_name;
    }

    void serialize(RingBuffer& rb) const
    {
      rb.write(command_name.data(), command_name.size());

      switch (mode_)
      {
      case devices::esp8266::Mode::Client:
        rb.write('1');
        break;
      
      case devices::esp8266::Mode::AccessPoint:
        rb.write('2');
        break;
      }
    }
  };

}