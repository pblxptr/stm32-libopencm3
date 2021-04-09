#include <drivers/gmock_uart_driver.hpp>

#include "../../src/esp8266wlan.cpp"

using namespace drivers::uart;

//Esp8266Wlan
template Esp8266Wlan<GMockUartDriver>::Esp8266Wlan(IUartDriver<GMockUartDriver>*);
template bool Esp8266Wlan<GMockUartDriver>::reset();