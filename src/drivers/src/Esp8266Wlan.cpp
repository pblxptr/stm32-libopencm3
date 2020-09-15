#include <Esp8266Wlan.hpp>

extern "C" {
  #include <libopencm3/stm32/rcc.h>
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/cm3/nvic.h>
  #include <libopencm3/stm32/dma.h>
  #include <libopencm3/stm32/usart.h>
}

using namespace drivers;

namespace {
  static constexpr size_t BUFFER_SIZE = 64;

  [[maybe_unused]]
  static uint8_t receive_buff[BUFFER_SIZE];

[[maybe_unused]]
void dma_receive(const Esp8266WlanHwCfg& hw_cfg, uint8_t* buff, size_t buff_size)
{
	dma_channel_reset(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id);

	dma_set_peripheral_address(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id, hw_cfg.usart_dr_addr);
	dma_set_memory_address(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id, reinterpret_cast<uint32_t>(buff));
	dma_set_number_of_data(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id, buff_size);
	dma_set_read_from_peripheral(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id);
	dma_enable_memory_increment_mode(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id);
  dma_enable_circular_mode(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id);
	dma_set_peripheral_size(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id, DMA_CCR_PSIZE_8BIT);
	dma_set_memory_size(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id, DMA_CCR_MSIZE_8BIT);
	dma_set_priority(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id, DMA_CCR_PL_HIGH);

	dma_enable_transfer_complete_interrupt(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id);
  dma_enable_half_transfer_interrupt(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id);

	dma_enable_channel(hw_cfg.dma_id, hw_cfg.dma_rx_channel_id);

  usart_enable_rx_dma(hw_cfg.usart_id);
}

}

namespace drivers {

Esp8266Wlan::Esp8266Wlan(const Esp8266WlanHwCfg& hw_cfg)
  : hw_cfg_{hw_cfg} {}

void Esp8266Wlan::init()
{
  /// USART && hw_cfg_.dma_id
  // -> RCC
  rcc_periph_clock_enable(RCC_USART1);
  rcc_periph_clock_enable(RCC_DMA1);

  // -> GPIO
  gpio_set_mode(GPIO_BANK_USART1_TX, GPIO_MODE_OUTPUT_50_MHZ, 
    GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

  gpio_set_mode(GPIO_BANK_USART1_RX, GPIO_MODE_INPUT, 
    GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, GPIO_USART1_RX);

  // -> Configuration
  usart_set_mode(hw_cfg_.usart_id, USART_MODE_TX_RX);
  usart_set_baudrate(hw_cfg_.usart_id, 9600);
  usart_set_parity(hw_cfg_.usart_id, USART_PARITY_NONE);
  usart_set_databits(hw_cfg_.usart_id, 8);
  usart_set_stopbits(hw_cfg_.usart_id, 1);
  usart_set_flow_control(hw_cfg_.usart_id, USART_FLOWCONTROL_NONE);
  usart_enable_rx_interrupt(hw_cfg_.usart_id);

  // nvic_enable_irq(hw_cfg_.usart_nvic_irq);

  // -> Enable 
  usart_enable(hw_cfg_.usart_id);

  //Enable DMA_RX IRQ
  nvic_set_priority(hw_cfg_.dma_rx_nvic_irq, 0);
	nvic_enable_irq(hw_cfg_.dma_rx_nvic_irq);

}

void Esp8266Wlan::connect_ap(std::string_view ssid, std::string_view password)
{
  [[maybe_unused]] auto x = ssid;
  [[maybe_unused]] auto y = password;

  // dma_receive(hw_cfg_, receive_buff, sizeof(receive_buff));

}

void Esp8266Wlan::set_mode(Esp8266WlanMode mode)
{
  [[maybe_unused]] auto x = mode;
}  

//API

Esp8266WlanConnectionId_t Esp8266Wlan::connect([[maybe_unused]] const std::string_view addr, [[maybe_unused]]uint16_t port)
{
  return static_cast<std::underlying_type_t<StatusCode>>(StatusCode::FAILED);
}

StatusCode Esp8266Wlan::async_receive(const Esp8266WlanConnectionId_t conn_id, uint8_t* buff, const size_t size, CompletitionHandler_t handler)
{
  auto& connection = connections_[conn_id];

  if (!connection.is_active)
  {
    return StatusCode::FAILED;
  }

  connection.receive_buff = buff;
  connection.receive_size = size;
  connection.receive_handler = handler;

  return StatusCode::SUCCESS;
}

}


void usart1_isr()
{
  if (usart_get_flag(USART1, USART_FLAG_IDLE))
  {
  }
} 

void dma1_channel5_isr(void)
{
  if (dma_get_interrupt_flag(USART1, DMA_CHANNEL5, DMA_TCIF))
  {
    [[maybe_unused]] int x = 10;
    dma_clear_interrupt_flags(USART1, DMA_CHANNEL5, DMA_TCIF);
  }

  else if (dma_get_interrupt_flag(USART1, DMA_CHANNEL5, DMA_HTIF))
  {
    [[maybe_unused]] int x = 10;
    dma_clear_interrupt_flags(USART1, DMA_CHANNEL5, DMA_HTIF);
  }

  else if (dma_get_interrupt_flag(USART1, DMA_CHANNEL5, DMA_TEIF))
  {
    [[maybe_unused]] int x = 10;
        dma_clear_interrupt_flags(USART1, DMA_CHANNEL5, DMA_TEIF);
  }
}