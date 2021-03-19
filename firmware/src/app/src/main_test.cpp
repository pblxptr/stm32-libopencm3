extern "C" {
  #include <libopencm3/stm32/rcc.h>
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/cm3/systick.h>
  #include <libopencm3/stm32/timer.h>
  #include <libopencm3/cm3/nvic.h>
  #include <libopencm3/stm32/usart.h>
  #include <libopencm3/stm32/dma.h>
  #include <libopencm3/stm32/rcc.h>
}

static void rcc_setup()
{
  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}

static inline void usart_enable_idle_interrupt(uint32_t usart)
{
  USART_CR1(usart) |= USART_CR1_IDLEIE;
}

static inline void usart_disable_idle_interrupt(uint32_t usart)
{
  USART_CR1(usart) &= ~USART_CR1_IDLEIE;
}

static inline void usart_clear_idle_flag([[maybe_unused]]uint32_t usart)
{
    // __IO uint32_t tmpreg;
    // tmpreg = USART1_SR;
    // (void) tmpreg;
    // tmpreg = USART1_DR;
    // (void) tmpreg;
}

void dma_receive(uint32_t dma, uint32_t stream, uint8_t* buff, uint32_t sz)
{
    // dma_disable_stream(dma, stream);
    dma_set_memory_address(dma, stream, (uint32_t) buff);
    dma_set_number_of_data(dma, stream, sz);
    dma_enable_transfer_complete_interrupt(dma, stream);
    dma_enable_stream(dma, stream);
}


void dma_receive2(uint32_t dma, uint32_t stream, uint8_t* buff, uint32_t sz)
{
  dma_disable_stream(DMA2, DMA_STREAM2);
  dma_stream_reset(DMA2, DMA_STREAM2);
  dma_set_peripheral_address(DMA2, DMA_STREAM2, reinterpret_cast<uint32_t>(&USART_DR(USART1)));
  dma_channel_select(DMA2, DMA_STREAM2, DMA_SxCR_CHSEL_4);
  dma_set_priority(DMA2, DMA_STREAM2, DMA_SxCR_PL_MEDIUM);
  dma_set_memory_size(DMA2, DMA_STREAM2, DMA_SxCR_MSIZE_8BIT);
  dma_set_peripheral_size(DMA2, DMA_STREAM2, DMA_SxCR_PSIZE_8BIT);
  dma_enable_memory_increment_mode(DMA2, DMA_STREAM2);
  dma_enable_circular_mode(DMA2, DMA_STREAM2);
  dma_set_transfer_mode(DMA2, DMA_STREAM2, DMA_SxCR_DIR_PERIPHERAL_TO_MEM);
  dma_set_memory_address(dma, stream, (uint32_t) buff);
  dma_set_number_of_data(dma, stream, sz);
  dma_enable_transfer_complete_interrupt(dma, stream);
  dma_enable_stream(dma, stream);
}

void dma_send(uint32_t dma, uint32_t stream, uint8_t* buff, uint32_t sz)
{
    dma_disable_stream(dma, stream);
    dma_set_memory_address(dma, stream, (uint32_t) buff);
    dma_set_number_of_data(dma, stream, sz);
    dma_enable_transfer_complete_interrupt(dma, stream);
    dma_enable_stream(dma, stream);
}

volatile uint8_t recv_buff[64];
volatile uint8_t send_buff[64] = "AT+CWMODE=1\r\n";

static inline void uart_clear_idle_flag(uint32_t uart_id)
{
  [[maybe_unused]] auto sr = USART_SR(uart_id);
  [[maybe_unused]] auto dr = USART_DR(uart_id);
}

void usart1_isr()
{
  volatile int x = 10;

  uint32_t nbytes = dma_get_number_of_data(DMA2, DMA_STREAM2);

  volatile uint8_t xd = 10; 

  if ((USART_CR1(USART1) & USART_CR1_IDLEIE) && 
      (USART_SR(USART1) & USART_FLAG_IDLE) 
      )
  {
    uart_clear_idle_flag(USART1);
  }
}

void usart2_isr()
{
  volatile int x = 10;

  volatile uint8_t xd = 10; 

  if ((USART_CR1(USART2) & USART_CR1_IDLEIE) && 
      (USART_SR(USART2) & USART_FLAG_IDLE) 
      )
  {
    uart_clear_idle_flag(USART2);
  }
}

void configure_usart1()
{
  rcc_periph_clock_enable(RCC_USART1);

  // -> GPIO
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);

  // -> Configuration
  usart_set_mode(USART1, USART_MODE_RX);
  usart_set_baudrate(USART1, 115200);
  usart_set_parity(USART1, USART_PARITY_NONE);
  usart_set_databits(USART1, 8);
  usart_set_stopbits(USART1, 1);
  usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
  usart_enable_idle_interrupt(USART1);

  nvic_enable_irq(NVIC_USART1_IRQ);
}

void configure_usart2()
{
  rcc_periph_clock_enable(RCC_USART2);

  // -> GPIO
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);

  // -> Configuration
  usart_set_mode(USART2, USART_MODE_TX_RX);
  usart_set_baudrate(USART2, 9600);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, 1);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
  usart_enable_idle_interrupt(USART2);

  nvic_enable_irq(NVIC_USART2_IRQ);
}

int main()
{
  rcc_setup();
  

  // nvic_enable_irq(NVIC_DMA2_STREAM2_IRQ);
  // nvic_enable_irq(NVIC_DMA2_STREAM7_IRQ);

  configure_usart1();
  usart_enable(USART1);

  //DMA
  // dma_disable_stream(DMA2, DMA_STREAM2);
  // dma_stream_reset(DMA2, DMA_STREAM2);
  // dma_set_peripheral_address(DMA2, DMA_STREAM2, reinterpret_cast<uint32_t>(&USART_DR(USART1)));
  // dma_channel_select(DMA2, DMA_STREAM2, DMA_SxCR_CHSEL_4);
  // dma_set_priority(DMA2, DMA_STREAM2, DMA_SxCR_PL_MEDIUM);
  // dma_set_memory_size(DMA2, DMA_STREAM2, DMA_SxCR_MSIZE_8BIT);
  // dma_set_peripheral_size(DMA2, DMA_STREAM2, DMA_SxCR_PSIZE_8BIT);
  // dma_enable_memory_increment_mode(DMA2, DMA_STREAM2);
  // dma_enable_circular_mode(DMA2, DMA_STREAM2);
  // dma_set_transfer_mode(DMA2, DMA_STREAM2, DMA_SxCR_DIR_PERIPHERAL_TO_MEM);

  // dma_set_memory_address(DMA2, DMA_STREAM2, (uint32_t) recv_buff);
  // dma_set_number_of_data(DMA2, DMA_STREAM2, sizeof(recv_buff));
  // dma_enable_transfer_complete_interrupt(DMA2, DMA_STREAM2);
  // dma_enable_stream(DMA2, DMA_STREAM2);

  // // -> TX dma
  // dma_disable_stream(DMA2, DMA_STREAM7);
  // dma_stream_reset(DMA2, DMA_STREAM7);
  // dma_set_peripheral_address(DMA2, DMA_STREAM7, reinterpret_cast<uint32_t>(&USART_DR(USART1)));
  // dma_channel_select(DMA2, DMA_STREAM7, DMA_SxCR_CHSEL_4);
  // dma_set_priority(DMA2, DMA_STREAM7, DMA_SxCR_PL_MEDIUM);
  // dma_set_memory_size(DMA2, DMA_STREAM7, DMA_SxCR_MSIZE_8BIT);
  // dma_set_peripheral_size(DMA2, DMA_STREAM7, DMA_SxCR_PSIZE_8BIT);
  // dma_enable_memory_increment_mode(DMA2, DMA_STREAM7);
  // dma_set_transfer_mode(DMA2, DMA_STREAM7, DMA_SxCR_DIR_MEM_TO_PERIPHERAL);

  //Fwd function when RX
  //Allow DMA to take control
  // usart_enable_rx_dma(USART1);
  // usart_enable_tx_dma(USART1);

  //dma_receive(DMA2, DMA_STREAM2, recv_buff, sizeof(recv_buff));
  //dma_send(DMA2, DMA_STREAM7, send_buff, 14);

  while(true);

}



