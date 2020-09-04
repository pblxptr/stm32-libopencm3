#include <Esp8266Wlan.hpp>

extern "C" {
  #include <libopencm3/stm32/rcc.h>
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/cm3/nvic.h>
  #include <libopencm3/stm32/dma.h>
  #include <libopencm3/stm32/usart.h>
}

namespace {
  struct DmaGeneralCfg {
    uint32_t dma;
    uint32_t dma_channel;
    uint32_t periph_addr;
    uint32_t usart_id;
    uint32_t nvic_irq;
  };

  static constexpr size_t READ_BUFFER_SIZE = 64;

  [[maybe_unused]]
  static uint8_t read_buffer[READ_BUFFER_SIZE];

  const static DmaGeneralCfg dma_cfg {
    DMA1,
    DMA_CHANNEL5, 
    reinterpret_cast<uint32_t>(&USART1_DR),
    USART1,
    NVIC_DMA1_CHANNEL5_IRQ
  };

}

 char data[64];
 size_t size = sizeof(data);

void dma2_req()
{
	dma_channel_reset(DMA1, DMA_CHANNEL5);

	dma_set_peripheral_address(DMA1, DMA_CHANNEL5, (uint32_t)&USART1_DR);
	dma_set_memory_address(DMA1, DMA_CHANNEL5, (uint32_t)data);
	dma_set_number_of_data(DMA1, DMA_CHANNEL5, size);
	dma_set_read_from_peripheral(DMA1, DMA_CHANNEL5);
	dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL5);
	dma_set_peripheral_size(DMA1, DMA_CHANNEL5, DMA_CCR_PSIZE_8BIT);
	dma_set_memory_size(DMA1, DMA_CHANNEL5, DMA_CCR_MSIZE_8BIT);
	dma_set_priority(DMA1, DMA_CHANNEL5, DMA_CCR_PL_HIGH);

	dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL5);

	dma_enable_channel(DMA1, DMA_CHANNEL5);

  usart_enable_rx_dma(USART1);
}

namespace drivers {

Esp8266Wlan::Esp8266Wlan(uint32_t usart)
  : usart_{usart} {}

void Esp8266Wlan::init()
{
  /// USART && DMA1
  // -> RCC
  rcc_periph_clock_enable(RCC_USART1);
  rcc_periph_clock_enable(RCC_DMA1);
  

  // -> GPIO
  gpio_set_mode(GPIO_BANK_USART1_TX, GPIO_MODE_OUTPUT_50_MHZ, 
    GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

  gpio_set_mode(GPIO_BANK_USART1_RX, GPIO_MODE_INPUT, 
    GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, GPIO_USART1_RX);

  // -> Configuration
  usart_set_mode(USART1, USART_MODE_TX_RX);
  usart_set_baudrate(USART1, 9600);
  usart_set_parity(USART1, USART_PARITY_NONE);
  usart_set_databits(USART1, 8);
  usart_set_stopbits(USART1, 1);
  usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
  // usart_enable_rx_interrupt(USART1);

  // -> ISR
  // nvic_enable_irq(NVIC_USART1_IRQ);
  
  // -> Enable 
  usart_enable(USART1);

	nvic_set_priority(NVIC_DMA1_CHANNEL5_IRQ, 0);
	nvic_enable_irq(NVIC_DMA1_CHANNEL5_IRQ);

}

void Esp8266Wlan::connect_ap(std::string_view ssid, std::string_view password)
{
  [[maybe_unused]] auto x = ssid;
  [[maybe_unused]] auto y = password;

  // dma_read(dma_cfg, read_buffer, sizeof(read_buffer));
  dma2_req();

}

void Esp8266Wlan::set_mode(Esp8266WlanMode mode)
{
  [[maybe_unused]] auto x = mode;
}  

//ISR
// void usart1_isr()
// {
  // if (usart_get_flag(USART1, USART_FLAG_TXE) != 0) 
  // {
  //   sendData();
  // }

  // if (usart_get_flag(USART1, USART_FLAG_RXNE) != 0) // when data is ready to read
  // {
  //   readData(); 
  // }
// } 
} //namespace drivers

// void usart1_isr()
// {
//   if (usart_get_flag(USART1, USART_FLAG_TXE) != 0) 
//   {
//     [[maybe_unused]] int x = 10;
//   }

//   if (usart_get_flag(USART1, USART_FLAG_RXNE) != 0) // when data is ready to read
//   {
//     [[maybe_unused]]
//     auto data = usart_recv(USART1);
//     [[maybe_unused]] int x = 10;
//   }
// } 

void dma1_channel5_isr(void)
{
  if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_HTIF))
  {
    [[maybe_unused]] int x = 10;
  }
  else if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_TCIF))
  {
    [[maybe_unused]] int x = 10;
  }
  else if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_TEIF))
  {
    [[maybe_unused]] int x = 10;
  }
}