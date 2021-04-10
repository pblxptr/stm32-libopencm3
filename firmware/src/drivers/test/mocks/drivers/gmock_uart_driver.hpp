#include <drivers/uart.hpp>
#include <gmock/gmock.h>

namespace drivers::uart
{
  class GMockUartDriver : public IUartDriver<GMockUartDriver>
  {
  public:
    MOCK_METHOD(void, set_rx_completed_callback, (rx_completed_t), ());
    MOCK_METHOD(void, set_rx_end_callback, (rx_end_t), ());
    MOCK_METHOD(void, set_tx_completed_callback, (tx_completed_t), ());
    MOCK_METHOD(void, set_rx_event_context, (void*), ());
    MOCK_METHOD(void, set_tx_event_context, (void*), ());
    MOCK_METHOD(size_t, receive, (uint8_t*, const size_t, const std::chrono::milliseconds&), ());
    MOCK_METHOD(void, send, (uint8_t*, size_t), ());
  };
}