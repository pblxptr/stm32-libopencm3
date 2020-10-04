#include<hal/uart.hpp>
#include<platform/peripherals.hpp>

using namespace drivers::uart;

namespace hal::uart
{ 
  void init()
  {
    // constexpr auto uarts = platform::peripherals::gpio::gpios_num();
    // constexpr auto uarts_num = platform::peripherals::gpio::gpios_num();



    // platform::hal::uart::init();
  }

  template<auto uart_id>
  void receive_poll([[maybe_unused]]StaticUartDriver<uart_id>*, [[maybe_unused]]Buffer_ptr_t, [[maybe_unused]]size_t sz)
  {
  }

  template void receive_poll<1073811456ul>(StaticUartDriver<1073811456ul>*, Buffer_ptr_t, size_t sz);
}