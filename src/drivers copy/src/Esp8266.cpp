// #include <Esp8266.hpp>

// #include <RingBuffer.hpp>

// extern "C" {
//   #include <libopencm3/stm32/rcc.h>
//   #include <libopencm3/stm32/gpio.h>
//   #include <libopencm3/cm3/nvic.h>
//   #include <libopencm3/stm32/dma.h>
//   #include <libopencm3/stm32/usart.h>
// }

// using namespace drivers::esp8266;
// using namespace utils::containers;

// namespace {
//   static constexpr uint8_t MAX_CONNECTIONS = 4;
//   static constexpr uint32_t DMA_BUFFER_SIZE = 64;
//   static constexpr uint32_t RING_BUFFER_SIZE = 128;

//   static uint8_t rx_dma_buffer[DMA_BUFFER_SIZE];
//   static uint8_t rx_rb_buffer[RING_BUFFER_SIZE];

//   static WlanHwCfg wlan_hw_cfg;
//   static RingBuffer rx_rb{rx_rb_buffer, RING_BUFFER_SIZE};
  
//   [[maybe_unused]]void dma_receive(uint8_t* buff, size_t buff_size)
//   {
//     dma_channel_reset(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id);

//     dma_set_peripheral_address(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id, wlan_hw_cfg.usart_dr_addr);
//     dma_set_memory_address(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id, reinterpret_cast<uint32_t>(buff));
//     dma_set_number_of_data(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id, buff_size);
//     dma_set_read_from_peripheral(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id);
//     dma_enable_memory_increment_mode(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id);
//     dma_enable_circular_mode(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id);
//     dma_set_peripheral_size(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id, DMA_CCR_PSIZE_8BIT);
//     dma_set_memory_size(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id, DMA_CCR_MSIZE_8BIT);
//     dma_set_priority(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id, DMA_CCR_PL_HIGH);

//     dma_enable_transfer_complete_interrupt(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id);
//     dma_enable_half_transfer_interrupt(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id);

//     nvic_set_priority(wlan_hw_cfg.dma_rx_nvic_irq, 0);
//     nvic_enable_irq(wlan_hw_cfg.dma_rx_nvic_irq);

//     dma_enable_channel(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id);

//     usart_enable_rx_dma(wlan_hw_cfg.usart_id);
//   }

//   /**
//    *  called mainly in interrupts 
//    */
//   [[maybe_unused]] void process_rx()
//   {
//     static size_t last_position = 0;

//     const size_t current_position = dma_get_number_of_data(wlan_hw_cfg.dma_id, wlan_hw_cfg.dma_rx_channel_id);

//     //There is some data in  rx_dma_buffer.
//     if (current_position != last_position)
//     {
//       //Case 1 -> normal linear mode.
//       if (current_position > last_position)
//       {
//         rx_rb.write(&rx_dma_buffer[last_position], current_position - last_position);
//       }
//       //Case 3 -> overflow mode.
//       else
//       {
//         rx_rb.write(&rx_dma_buffer[last_position], DMA_BUFFER_SIZE - last_position - current_position);
//         rx_rb.write(&rx_dma_buffer[0], current_position);
//       }
//     }

//     last_position = current_position % sizeof(rx_dma_buffer);

//     [[maybe_unused]] int x = 10;
//   }
// }

// namespace drivers::esp8266
// {
//   void init(const WlanHwCfg& hw_cfg)
//   {
//     wlan_hw_cfg = hw_cfg;

//     /// USART && wlan_hw_cfg.dma_id
//     // -> RCC
//     rcc_periph_clock_enable(RCC_USART1);
//     rcc_periph_clock_enable(RCC_DMA1);

//     // -> GPIO
//     gpio_set_mode(GPIO_BANK_USART1_TX, GPIO_MODE_OUTPUT_50_MHZ, 
//       GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

//     gpio_set_mode(GPIO_BANK_USART1_RX, GPIO_MODE_INPUT, 
//       GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, GPIO_USART1_RX);

//     // -> Configuration
//     usart_set_mode(wlan_hw_cfg.usart_id, USART_MODE_TX_RX);
//     usart_set_baudrate(wlan_hw_cfg.usart_id, 9600);
//     usart_set_parity(wlan_hw_cfg.usart_id, USART_PARITY_NONE);
//     usart_set_databits(wlan_hw_cfg.usart_id, 8);
//     usart_set_stopbits(wlan_hw_cfg.usart_id, 1);
//     usart_set_flow_control(wlan_hw_cfg.usart_id, USART_FLOWCONTROL_NONE);

//     // USART_CR1(USART1) |= USART_CR1_IDLEIE;
//     usart_enable_rx_interrupt(USART1);

//     nvic_enable_irq(wlan_hw_cfg.usart_nvic_irq);

//     dma_receive(rx_dma_buffer, DMA_BUFFER_SIZE);

//     // -> Enable 
//     usart_enable(wlan_hw_cfg.usart_id);

//   }

//   void set_mode(const WlanMode& wlan_mode)
//   {
//     [[maybe_unused]] auto x = wlan_mode;
//   }

//   void connect_ap(const std::string_view ssid, const std::string_view password)
//   {
//     [[maybe_unused]] auto x = ssid;
//     [[maybe_unused]] auto y = password;
//   }

//   void process()
//   {

//   }
// }

// #define __IO volatile

// //Interrupts 
// void usart1_isr()
// {
//   __IO uint32_t tmpreg;
//   tmpreg = USART1_SR;
//   (void) tmpreg;
//   tmpreg = USART1_DR;
//   (void) tmpreg;

// }

// void dma1_channel5_isr(void)
// {
//   if (dma_get_interrupt_flag(USART1, DMA_CHANNEL5, DMA_TCIF))
//   {
//     // process_rx();
//     dma_clear_interrupt_flags(USART1, DMA_CHANNEL5, DMA_TCIF);
//   }

//   else if (dma_get_interrupt_flag(USART1, DMA_CHANNEL5, DMA_HTIF))
//   {
//     // process_rx();
//     dma_clear_interrupt_flags(USART1, DMA_CHANNEL5, DMA_HTIF);
//   }

//   else if (dma_get_interrupt_flag(USART1, DMA_CHANNEL5, DMA_TEIF))
//   {
//     // process_rx();
//     dma_clear_interrupt_flags(USART1, DMA_CHANNEL5, DMA_TEIF);
//   }
// }