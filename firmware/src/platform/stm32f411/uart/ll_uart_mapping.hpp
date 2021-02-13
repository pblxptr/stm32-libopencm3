#pragma once

#include <plt_hal.hpp>
#include <drivers/uart.hpp>

extern "C" {
  #include <libopencm3/stm32/usart.h>
}

namespace platform::ll_drivers::uart
{
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
      return platform::hal::HAL_INVALID_VALUE;
  }

  template<drivers::uart::Baudrate baudrate>
  constexpr int32_t get_baudate()
  {
    if constexpr(baudrate == drivers::uart::Baudrate::B_9600)
      return 9600;
    else if constexpr(baudrate == drivers::uart::Baudrate::B_115200)
      return 115200;
    else 
      return platform::hal::HAL_INVALID_VALUE;
  }

  template<drivers::uart::Parity parity>
  constexpr int32_t get_parity()
  {
    if constexpr(parity == drivers::uart::Parity::EVEN)
      return USART_PARITY_EVEN;
    else if constexpr(parity == drivers::uart::Parity::ODD)
      return USART_PARITY_ODD;
    else if constexpr(parity == drivers::uart::Parity::NONE)
      return USART_PARITY_NONE;
    else 
      return platform::hal::HAL_INVALID_VALUE;
  }

  template<drivers::uart::DataBits databits>
  constexpr int32_t get_databits()
  {
    if constexpr(databits == drivers::uart::DataBits::D_8)
      return 8;
    else if constexpr(databits == drivers::uart::DataBits::D_9)
      return 9;
    else 
      return platform::hal::HAL_INVALID_VALUE;
  }

  template<drivers::uart::StopBits stopbits>
  constexpr int32_t get_stopbits()
  {
    if constexpr(stopbits == drivers::uart::StopBits::S_1)
      return 1;
    else
      return platform::hal::HAL_INVALID_VALUE;
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
      return platform::hal::HAL_INVALID_VALUE;
  }
}