#pragma once

#include <utils/ring_buffer.hpp>

namespace devices::esp8266
{
  class ResetCommand
  {
  public:
    static constexpr std::string_view command_name = "AT+RST";

    constexpr std::string_view command() const 
    {
      return command_name;
    }

    void serialize(RingBuffer& rb) const
    {
      rb.write(command_name.data(), command_name.size());
    }
  };

}