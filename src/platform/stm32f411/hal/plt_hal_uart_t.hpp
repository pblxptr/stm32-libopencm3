#pragma once

#include<stdint.h>
#include<plt_hal_uart_base.hpp>
#include<drivers/uart.hpp>

extern "C" {
  #include<libopencm3/stm32/usart.h>
  #include<libopencm3/stm32/gpio.h>
}

namespace {
  template<uint32_t uart_id>
  constexpr platform::hal::uart::Pinout get_pinout()
  {
    if constexpr(uart_id == USART1) 
      return platform::hal::uart::Pinout{GPIOA, GPIO1, GPIO2 };
    else if constexpr(uart_id == USART2) 
      return platform::hal::uart::Pinout{GPIOA, GPIO3, GPIO2 };
    else 
      return platform::hal::uart::Pinout{
        platform::hal::uart::INVALID_PORT, 
        platform::hal::uart::INVALID_PORT, 
        platform::hal::uart::INVALID_PORT
      };
  }

  template<drivers::uart::Mode mode>
  constexpr int32_t get_mode()
  {
    if constexpr(mode == drivers::uart::Mode::RX)
      return USART_MODE_RX;
    else if constexpr(mode == drivers::uart::Mode::TX)
      return USART_MODE_TX;
    else if constexpr(mode == drivers::uart::Mode::RX_TX)
      return USART_MODE_TX_RX;
    else 
      return platform::hal::uart::INVALID_MODE;
  }

  template<drivers::uart::Baudrate baudrate>
  constexpr int32_t get_baudate()
  {
    if constexpr(baudrate == drivers::uart::Baudrate::B_9600)
      return 9600;
    else if constexpr(baudrate == drivers::uart::Baudrate::B_11200)
      return 11200;
    else 
      return platform::hal::uart::INVALID_BAUDRATE;
  }

  template<drivers::uart::Parity parity>
  constexpr int32_t get_parity()
  {
    if constexpr(parity == drivers::uart::Parity::EVEN)
      return USART_PARITY_EVEN;
    else if constexpr(parity == drivers::uart::Parity::ODD)
      return USART_PARITY_ODD;
    else 
      return USART_PARITY_NONE;
  }

  template<drivers::uart::DataBits databits>
  constexpr int32_t get_databits()
  {
    if constexpr(databits == drivers::uart::DataBits::D_8)
      return 8;
    else if constexpr(databits == drivers::uart::DataBits::D_9)
      return 9;
    else 
      return platform::hal::uart::INVALID_DATABITS;
  }

  template<drivers::uart::StopBits stopbits>
  constexpr int32_t get_stopbits()
  {
    if constexpr(stopbits == drivers::uart::StopBits::S_1)
      return 1;
    else
      return platform::hal::uart::INVALID_STOPBITS;
  }

  template<drivers::uart::FlowControl flow_control>
  constexpr int32_t get_flow_control()
  {
    if constexpr(flow_control == drivers::uart::FlowControl::CTS)
      return USART_FLOWCONTROL_CTS;
    else if constexpr(flow_control == drivers::uart::FlowControl::RTS)
      return USART_FLOWCONTROL_RTS;
    else if constexpr(flow_control == drivers::uart::FlowControl::RTS_CTS)
      return USART_FLOWCONTROL_RTS_CTS;
    else if constexpr(flow_control == drivers::uart::FlowControl::NONE)
      return USART_FLOWCONTROL_NONE;
    else 
      return platform::hal::uart::INVALID_FLOW_CONTROL;
  }
}

namespace platform::hal::uart
{
  void init();
  template<class TUartDriver, class TConfig>
  void setup()
  {
    using UartDriver = TUartDriver;
    using Config = TConfig;

    //Configure pins
    constexpr auto pinout = get_pinout<UartDriver::uart_id>();
    static_assert(pinout.port != platform::hal::uart::INVALID_PORT);
    static_assert(pinout.rx_pin != platform::hal::uart::INVALID_PIN);
    static_assert(pinout.tx_pin != platform::hal::uart::INVALID_PIN);

  	gpio_mode_setup(pinout.port, GPIO_MODE_AF, GPIO_PUPD_NONE, pinout.rx_pin | pinout.tx_pin);
	  gpio_set_af(pinout.port, GPIO_AF7, pinout.rx_pin | pinout.tx_pin);

    //Configure mode
    constexpr auto mode = get_mode<Config::mode>();
    static_assert(mode != platform::hal::uart::INVALID_MODE);
    usart_set_mode(UartDriver::uart_id, mode);

    //Configure baudrate
    constexpr auto baudrate = get_baudate<Config::baudrate>();
    static_assert(baudrate != platform::hal::uart::INVALID_BAUDRATE);
    usart_set_baudrate(UartDriver::uart_id, baudrate);

    //Configure parity
    constexpr auto parity = get_parity<Config::parity>();
    static_assert(parity != platform::hal::uart::INVALID_PARITY);
    usart_set_parity(UartDriver::uart_id, parity);

    //Configure databits
    constexpr auto databits = get_databits<Config::databits>();
    static_assert(databits != platform::hal::uart::INVALID_DATABITS);
    usart_set_databits(UartDriver::uart_id, databits);
    
    //Configure stopbits
    constexpr auto stopbits = get_stopbits<Config::stopbits>();
    static_assert(stopbits != platform::hal::uart::INVALID_STOPBITS);
    usart_set_stopbits(UartDriver::uart_id, stopbits);

    //Configure flow control
    constexpr auto flow_control = get_flow_control<Config::flow_control>();
    static_assert(flow_control != platform::hal::uart::INVALID_FLOW_CONTROL);
    usart_set_flow_control(UartDriver::uart_id, flow_control);
  }
}