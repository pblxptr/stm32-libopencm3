#include <console_print.hpp>

#include <algorithm>

using namespace drivers::uart;


namespace {
  static constexpr size_t DEBUG_BUFFER_SIZE = 128;
  static constexpr std::string_view endline = "\r\n";
  static UartDriver* driver{nullptr};
  static uint8_t buffer[DEBUG_BUFFER_SIZE];
  volatile bool is_busy{false};

  void handle_sending_completed([[maybe_unused]] void* ctx)
  {
    is_busy = false;
  }
}
namespace utils::debug::console
{
  void set_uart_driver(drivers::uart::UartDriver* uart_driver)
  {
    driver = uart_driver;
    driver->tx_completed_cb = handle_sending_completed;
  }
  
  void print(const std::string_view sw)
  {
    is_busy = true;

    const size_t nbytes = std::min(sw.size() + endline.size(), DEBUG_BUFFER_SIZE);
    
    std::fill_n(buffer, DEBUG_BUFFER_SIZE, '\0');
    uint8_t* offset = buffer + nbytes - endline.size();

    for (size_t i = 0; i < endline.size(); ++i)
    {
      offset[i] = endline[i];
    }

    std::copy_n(sw.data(), nbytes - endline.size(), buffer);
    hal::uart::send(driver, buffer, DEBUG_BUFFER_SIZE);
    
    while(is_busy);
  }
}