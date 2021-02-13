#include <devices/esp8266wlan.hpp>
#include <console_print.hpp>
#include <thread>
#include <memory>
#include <chrono>
#include <fmt/core.h>
#include <iostream>

using namespace devices::esp8266;
using namespace drivers::uart;
using namespace utils::debug;

UartDriver esp_uart_driver;
UartDriver console_uart_driver;
std::unique_ptr<Esp8266Wlan> esp8266;
std::unique_ptr<std::thread> main_thread{nullptr};
std::unique_ptr<std::thread> dma_thread{nullptr};


void main_loop()
{
  std::cout << "Main Thread-" << std::this_thread::get_id() << " started.\n";
  esp_uart_driver.uart_id = 1;
  console_uart_driver.uart_id = 2;

  console::set_uart_driver(&console_uart_driver);

  esp8266 = std::make_unique<Esp8266Wlan>(&esp_uart_driver);
  esp8266->set_mode(devices::esp8266::Mode::Client);

  while(true)
  {
    console::task();
  //   esp8266->task();
  }
}

void dma_loop()
{
  std::cout << "Dma Thread-" << std::this_thread::get_id() << " started.\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  char response_buffer[] = "IPD+4,asAT+CWMODE=ASDADASD\r\nOK\r\n";
  auto response = std::string_view{response_buffer, sizeof(response_buffer) - 1};
  std::copy(response.begin(), response.end(), esp8266->rx_buffer_);
  esp8266->handle_rx_end(response.size());
}


int main()
{
  main_thread = std::make_unique<std::thread>(main_loop);

  dma_thread = std::make_unique<std::thread>(dma_loop);

  main_thread->join();
  dma_thread->join();

}