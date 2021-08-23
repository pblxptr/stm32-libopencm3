#include <drivers/uart.hpp>
#include <hal/uart.hpp>
#include <gsl/span>

namespace drivers::uart {
void UartDriver::set_rx_completed_callback(rx_completed_t cb) 
{
  rx_completed_cb = cb;
}

void UartDriver::set_rx_end_callback(rx_end_t cb)
{
  rx_end_cb = cb;
}

void UartDriver::set_tx_completed_callback(tx_completed_t cb)
{
  tx_completed_cb = cb;
}

void UartDriver::set_rx_event_context(void* ctx)
{
  rx_event_ctx = ctx;
}

void UartDriver::set_tx_event_context(void* ctx)
{
  rx_event_ctx = ctx;
}

size_t UartDriver::receive(gsl::span<uint8_t> buffer, const std::chrono::milliseconds& timeout)
{
  hal::uart::receive(this, buffer.data(), buffer.size());
  os::timer::wait(timeout);

  return 0; //TODO: Return valid number of bytes
}

void UartDriver::send(gsl::span<uint8_t> buffer)
{
  hal::uart::send(this, buffer.data(), buffer.size());
}

}