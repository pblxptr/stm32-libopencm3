#pragma once

#include <utils/ring_buffer.hpp>
#include <devices/esp8266wlan.hpp>
#include <array>

namespace devices::esp8266
{
  class CwJapCommand
  {
    std::array<char, 24> uuid_;
    std::array<char, 24> password_;
  public:
    static constexpr std::string_view command_name = "AT+CWJAP=";

    CwJapCommand(const std::string_view uuid, const std::string_view password) 
    {
      std::fill(uuid_.begin(), uuid_.end(), '\0');
      std::fill(password_.begin(), password_.end(), '\0');

      std::copy_n(uuid.begin(), std::min(uuid_.size() - 1, uuid.size()), uuid_.begin());
      std::copy_n(password.begin(), std::min(password_.size() - 1, password.size()), password_.begin());
    }

    constexpr std::string_view command() const 
    {
      return command_name;
    }

    void serialize(RingBuffer& rb) const
    {
      const std::string_view uuid{uuid_.begin()};
      const std::string_view password{password_.begin()};

      //Pattern "COMMAND="UUID","testestteasd"
      // -> Command
      rb.write(command_name.data(), command_name.size());

      // -> UUID
      rb.write('\"');
      rb.write(uuid.data(), uuid.size()); 
      rb.write('\"');

      // -> Separator
      rb.write(',');

      // -> Password
      rb.write('\"');
      rb.write(password.data(), password.size());
      rb.write('\"');
    }
  };

}