// #pragma once

// #include<plt_hal_uart_base.hpp>
// #include<drivers/uart.hpp>

// extern "C" {
//   #include <libopencm3/stm32/usart.h>
//   #include <libopencm3/stm32/rcc.h>
//   #include <libopencm3/stm32/gpio.h>
// }

// namespace {
//   platform::hal::uart::Pinout get_pinout([[maybe_unused]]uint32_t uartid)
//   {
//     //USART2
//     return platform::hal::uart::Pinout{GPIOA, GPIO3, GPIO2 };
//   }

//   uint32_t get_mode(const drivers::uart::Mode& mode)
//   {
//     if (mode == drivers::uart::Mode::RX)
//     {
//       return USART_MODE_RX;
//     }
//     else if (mode == drivers::uart::Mode::TX)
//     {
//       return USART_MODE_TX;
//     }
//     else 
//     {
//       return USART_MODE_TX_RX;
//     }
//   }

//   uint32_t get_baudrate([[maybe_unused]]const drivers::uart::Baudrate& baudrate)
//   {
//     return 9600;
//   }

//   uint32_t get_partity([[maybe_unused]] const drivers::uart::Parity& parity)
//   {
//     if (parity == drivers::uart::Parity::EVEN) 
//     {
//       return USART_PARITY_ODD;
//     }
//     else if (parity == drivers::uart::Parity::ODD)
//     {
//       return USART_PARITY_ODD;
//     }
//     else return USART_PARITY_NONE;
//   }

//   uint32_t get_databits(const drivers::uart::DataBits& databits)
//   {
//     if (databits == drivers::uart::DataBits::D_8)
//     {
//       return 8;
//     }
//     else 
//     {
//       return 9;
//     }
//   }

//   uint32_t get_stopbits([[maybe_unused]]const drivers::uart::StopBits& stopbits)
//   {
//     return 1;
//   }

//   uint32_t get_flow_control(const drivers::uart::FlowControl& flowcontrol)
//   {
//     if (flowcontrol == drivers::uart::FlowControl::RTS)
//     {
//       return USART_FLOWCONTROL_RTS;
//     }
//     else if (flowcontrol == drivers::uart::FlowControl::CTS)
//     {
//       return USART_FLOWCONTROL_CTS;
//     }
//     else if (flowcontrol == drivers::uart::FlowControl::RTS_CTS)
//     {
//       return USART_FLOWCONTROL_RTS_CTS;
//     }
//     else 
//     {
//       return USART_FLOWCONTROL_NONE;
//     }
//   }
// }

// namespace platform::hal::uart
// {
//   inline void init()
//   {
//     rcc_periph_clock_enable(RCC_USART1);
//   }

//   void setup(drivers::uart::UartDriver& driver, const drivers::uart::UartConfig& config)
//   {
//     rcc_periph_clock_enable(RCC_USART1);
//     rcc_periph_clock_enable(RCC_USART2);
    
//     //GPIO
//     const auto pinout = get_pinout(driver.id);

//   	gpio_mode_setup(pinout.port, GPIO_MODE_AF, GPIO_PUPD_NONE, pinout.rx_pin | pinout.tx_pin);

// 	  gpio_set_af(pinout.port, GPIO_AF7, pinout.rx_pin | pinout.tx_pin);

//     //USART
//     usart_set_mode(driver.id, get_mode(config.mode));
//     usart_set_baudrate(driver.id, get_baudrate(config.baudrate));
//     usart_set_parity(driver.id, get_partity(config.partiy));
//     usart_set_databits(driver.id, get_databits(config.data_bits));
//     usart_set_stopbits(driver.id, get_stopbits(config.stop_bits));
//     usart_set_flow_control(driver.id, get_flow_control(config.flow_control));
    
//     //Enable 
//     usart_enable(driver.id);
//   }
// }