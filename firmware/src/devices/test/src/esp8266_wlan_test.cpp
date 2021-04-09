#include <devices/esp8266wlan.hpp>
#include <devices/reset_command.hpp>

#include <memory>
#include <vector>
#include <gtest/gtest.h>

#include <drivers/gmock_uart_driver.hpp>

using namespace testing;
using namespace devices::esp8266;

namespace {
  constexpr std::string_view OPERATION_TERMINATOR{"\r\n"};
}

struct Esp8266WlanTest : public Test
{
  GMockUartDriver uart_;
  std::unique_ptr<Esp8266Wlan<GMockUartDriver>> sut_;

  void SetUp() override
  {
    EXPECT_CALL(uart_, set_rx_event_context(An<void*>()));
    EXPECT_CALL(uart_, set_rx_end_callback(An<rx_end_t>()));
    EXPECT_CALL(uart_, set_tx_event_context(An<void*>()));
    EXPECT_CALL(uart_, set_tx_completed_callback(An<tx_completed_t>()));

    ON_CALL(uart_, receive(An<uint8_t*>(), An<size_t>(), An<const std::chrono::milliseconds&>()))
      .WillByDefault(Return(0));

    sut_ = std::make_unique<Esp8266Wlan<GMockUartDriver>>(&uart_);

  }

  void TearDown() override
  {
    sut_.reset();
  }
};

TEST_F(Esp8266WlanTest, WhenTheResetMessageIsSentThenBlockingOperationShouldBePerformed)
{
  //Arrange
  constexpr auto count = 10;
  uint8_t* const expected_vector = new uint8_t[count]; 

  EXPECT_CALL(uart_, send(ElementsAreArray(expected_vector, count), _));

  //Act
  sut_->reset();

  //Assert
}