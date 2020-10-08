#pragma once

#include <drivers/uart.hpp>

extern "C" {
  #include <libopencm3/stm32/usart.h>
}

//Forward reference
namespace platform::ll_drivers::dma { struct DmaStream; }

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
    else if constexpr(parity == drivers::uart::Parity::NONE)
      return USART_PARITY_NONE;
    else 
      return platform::hal::uart::INVALID_PARITY;
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

  struct STM32UartDriver : drivers::uart::UartDriver2
  {
    using uart_irq_t = void(*)(void*);

    platform::ll_drivers::dma::DmaStream* rx_dma;
    platform::ll_drivers::dma::DmaStream* tx_dma;
    uart_irq_t fwd_isr;
    void* fwd_isr_ctx;

    STM32UartDriver()
      : rx_dma{nullptr}
      , tx_dma{nullptr}
      , fwd_isr{nullptr}
      , fwd_isr_ctx{nullptr} {}
  };

  template<uint32_t UART_ID>
  void configure_gpio();

  template<uint32_t UART_ID>
  void configure_interrupts();

  template<uint32_t UART_ID>
  void configure_dma(STM32UartDriver*);

  template<uint32_t UART_ID>
  constexpr STM32UartDriver* get_driver();
}