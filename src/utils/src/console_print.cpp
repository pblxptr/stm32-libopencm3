#include <console_print.hpp>
#include <ring_buffer.hpp>

#include <algorithm>

using namespace drivers::uart;
using namespace utils::containers;

namespace {
  UartDriver* driver{nullptr};
  static constexpr size_t DEBUG_BUFFER_SIZE = 512;
  static uint8_t rb_buffer[DEBUG_BUFFER_SIZE];
  static RingBuffer rb{rb_buffer, DEBUG_BUFFER_SIZE};
  static uint8_t send_buffer[DEBUG_BUFFER_SIZE];
}
namespace utils::debug::console
{
  void set_uart_driver(drivers::uart::UartDriver* uart_driver)
  {
    driver = uart_driver;

    print("Debug console enabled.\r\n");
  }
  
  void print(const std::string_view sw)
  {
    rb.write(reinterpret_cast<const uint8_t*>(sw.data()), sw.size());

    task(); //TODO: Test
  }

  void print(const uint8_t* buffer, size_t sz)
  {
    rb.write(buffer, sz); 
  }

  void print(RingBuffer& in_rb, size_t sz)
  {
    for (size_t i = 0; i < sz; ++i)
    {
      rb.write(in_rb.read());
    }
  }

  void task()
  {
    if (driver->tx_state == UartState::ACTIVE)
      return;

    const size_t capacity = rb.capacity();

    if (capacity == 0)
    {
      return;
    }

    std::fill_n(send_buffer, DEBUG_BUFFER_SIZE, '\0');
    for (size_t i = 0; i < capacity; ++i)
    {
      send_buffer[i] = rb.read();
    }

    hal::uart::send(driver, send_buffer, capacity);
  }
}