#pragma once

extern "C" {
  #include <libopencm3/stm32/usart.h>
  #include <libopencm3/stm32/rcc.h>
  #include <libopencm3/stm32/gpio.h>
}

#include<drivers/uart.hpp>

namespace {
  struct Pinout {
    uint32_t rx_port;
    uint32_t rx_pin;
    uint32_t tx_port;
    uint32_t tx_pin;
  };

  Pinout get_pinout(uint32_t uartid)
  {
    return Pinout{GPIO_BANK_USART1_RX, GPIO_USART1_RX,
      GPIO_BANK_USART1_TX, GPIO_USART1_TX
    };
  }

  uint32_t get_mode(const drivers::uart::Mode& mode)
  {
    if (mode == drivers::uart::Mode::RX)
    {
      return USART_MODE_RX;
    }
    else if (mode == drivers::uart::Mode::TX)
    {
      return USART_MODE_TX;
    }
    else 
    {
      return USART_MODE_TX_RX;
    }
  }

  uint32_t get_baudrate([[maybe_unused]]const drivers::uart::Baudrate& baudrate)
  {
    return 9600;
  }

  uint32_t get_partity([[maybe_unused]] const drivers::uart::Partiy& parity)
  {
    if (parity == drivers::uart::Partiy::EVEN) 
    {
      return USART_PARITY_ODD;
    }
    else if (parity == drivers::uart::Partiy::ODD)
    {
      return USART_PARITY_ODD;
    }
    else return USART_PARITY_NONE;
  }

  uint32_t get_databits(const drivers::uart::DataBits& databits)
  {
    if (databits == drivers::uart::DataBits::D_8)
    {
      return 8;
    }
    else 
    {
      return 9;
    }
  }

  uint32_t get_stopbits(const drivers::uart::StopBits& stopbits)
  {
    return 1;
  }

  uint32_t get_flow_control(const drivers::uart::FlowControl& flowcontrol)
  {
    if (flowcontrol == drivers::uart::FlowControl::RTS)
    {
      return USART_FLOWCONTROL_RTS;
    }
    else if (flowcontrol == drivers::uart::FlowControl::CTS)
    {
      return USART_FLOWCONTROL_CTS;
    }
    else if (flowcontrol == drivers::uart::FlowControl::RTS_CTS)
    {
      return USART_FLOWCONTROL_RTS_CTS;
    }
    else 
    {
      return USART_FLOWCONTROL_NONE;
    }
  }
}

namespace platform::hal::uart
{
  inline void init()
  {
    rcc_periph_clock_enable(RCC_USART1);
  }

  void setup(drivers::uart::UartDriver& driver, const drivers::uart::UartConfig& config)
  {
    rcc_periph_clock_enable(RCC_USART1);

    //GPIO
    gpio_set_mode(pinout.tx_port, GPIO_MODE_OUTPUT_50_MHZ, 
      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, pinout.tx_pin);

    gpio_set_mode(pinout.rx_port, GPIO_MODE_INPUT, 
      GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, pinout.rx_pin);

    //USART
    usart_set_mode(driver.id, get_mode(config.mode));
    usart_set_baudrate(driver.id, get_baudrate(config.baudrate));
    usart_set_parity(driver.id, get_partity(config.partiy));
    usart_set_databits(driver.id, get_databits(config.data_bits));
    usart_set_stopbits(driver.id, get_stopbits(config.stop_bits));
    usart_set_flow_control(driver.id, get_flow_control(config.flow_control));
    
    //Enable 
    usart_enable(driver.id);
  }
}