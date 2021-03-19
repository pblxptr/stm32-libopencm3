#include <gtest/gtest.h>
#include <Esp8266Wlan.hpp>
#include <iostream>

using namespace drivers;

namespace {
  struct PrintUsartDriver
  {
    void send(uint8_t* buff, size_t s)
    {
      auto command = std::string(buff, buff + s);

      std::cout << command << std::endl;
    }
  };
}

class Esp8266WlanTests : public ::testing::Test 
{

};

TEST_F(Esp8266WlanTests, WhenSettingModeThenAppropriateModeCommandShouldBeSent)
{
  auto usartDriver = PrintUsartDriver{};
  auto sut = Esp8266Wlan{usartDriver};

  sut.set_mode(Esp8266WlanMode::Client);
  sut.set_mode(Esp8266WlanMode::AccessPoint);
  sut.set_mode(Esp8266WlanMode::Both);

  sut.connect("SkalarKarol57", "password");
}
