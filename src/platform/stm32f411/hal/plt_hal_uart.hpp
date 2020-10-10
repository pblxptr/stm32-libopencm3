#pragma once

#include <stdint.h>
#include <plt_hal_uart_base.hpp>
#include <drivers/uart.hpp>
#include <ll_uart.hpp>

#include <cstddef>

extern "C" {
  #include <libopencm3/stm32/usart.h>
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/cm3/nvic.h>
  #include <libopencm3/stm32/dma.h>
  #include <libopencm3/stm32/rcc.h>
}

namespace {
  using namespace drivers::uart;
  using namespace platform::ll_drivers::uart;

}

namespace platform::hal::uart
{ 
  inline void _hal_handle_uart_isr([[maybe_unused]] void* ctx)
  {
    [[maybe_unused]] auto x = 10;
  }

  inline void init()
  {
    rcc_periph_clock_enable(RCC_USART1);
  }

  template<class TConfig>
  UartDriver2* setup()
  {
    using Config = TConfig;

    static_assert(Config::uart_id == USART1);

    //Configure GPIO for UART //TODO: Currently hardcoded for USART1
    platform::ll_drivers::uart::configure_gpio<Config::uart_id>();

    //Configure mode
    constexpr auto mode = get_mode<Config::mode>();
    static_assert(mode != platform::hal::uart::INVALID_MODE);
    usart_set_mode(Config::uart_id, mode);

    //Configure baudrate
    constexpr auto baudrate = get_baudate<Config::baudrate>();
    static_assert(baudrate != platform::hal::uart::INVALID_BAUDRATE);
    usart_set_baudrate(Config::uart_id, baudrate);

    //Configure parity
    constexpr auto parity = get_parity<Config::parity>();
    static_assert(parity != platform::hal::uart::INVALID_PARITY);
    usart_set_parity(Config::uart_id, parity);

    //Configure databits
    constexpr auto databits = get_databits<Config::databits>();
    static_assert(databits != platform::hal::uart::INVALID_DATABITS);
    usart_set_databits(Config::uart_id, databits);
    
    //Configure stopbits
    constexpr auto stopbits = get_stopbits<Config::stopbits>();
    static_assert(stopbits != platform::hal::uart::INVALID_STOPBITS);
    usart_set_stopbits(Config::uart_id, stopbits);

    //Configure flow control
    constexpr auto flow_control = get_flow_control<Config::flow_control>();
    static_assert(flow_control != platform::hal::uart::INVALID_FLOW_CONTROL);
    usart_set_flow_control(Config::uart_id, flow_control);

    //Configure interrupts TODO: Interrupts are enabled when recive is called, function below just enable interrupt in NVIC
    platform::ll_drivers::uart::configure_interrupts<Config::uart_id>();

    //Get driver 
    constexpr auto* driver = platform::ll_drivers::uart::get_driver<Config::uart_id>();
    static_assert(driver != nullptr, "Invalid driver selected. Possibly not yet implemented");
    driver->uart_id = Config::uart_id;
    driver->fwd_isr = _hal_handle_uart_isr;
    driver->fwd_isr_ctx = driver;

    //Configure DMA 
    platform::ll_drivers::uart::configure_dma<Config::uart_id>(driver);

    return driver;
  }

  inline void receive(drivers::uart::UartDriver2* driver, uint8_t* buff, size_t sz)
  {
    auto* stm_driver = reinterpret_cast<STM32UartDriver*>(driver); //TODO: Temp solution. Avoid downcasting
    // if (stm_driver->rx_end_cb != nullptr)
    // {
    //   //TODO: Enable idle interrupt
    // }

    // if (stm_driver->rx_every_byte != nullptr)
    // {
    //   //TODO: Enable interrupt ex
    // }

    usart_disable(stm_driver->uart_id);
    dma_disable_stream(stm_driver->rx_dma->dma, stm_driver->rx_dma->stream);
    dma_set_memory_address(stm_driver->rx_dma->dma, stm_driver->rx_dma->stream, (uint32_t) buff);
    dma_set_number_of_data(stm_driver->rx_dma->dma, stm_driver->rx_dma->stream, sz);
    dma_enable_transfer_complete_interrupt(stm_driver->rx_dma->dma, stm_driver->rx_dma->stream);
    dma_enable_stream(stm_driver->rx_dma->dma, stm_driver->rx_dma->stream);
    usart_enable_rx_dma(stm_driver->uart_id);
    usart_enable(stm_driver->uart_id);
  }
}