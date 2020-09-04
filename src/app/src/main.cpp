extern "C" {
  #include <libopencm3/stm32/rcc.h>
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/cm3/systick.h>
  #include <libopencm3/stm32/timer.h>
  #include <libopencm3/cm3/nvic.h>
  #include <libopencm3/stm32/usart.h>
  #include <libopencm3/stm32/dma.h>
}

#include <Os.hpp>
#include <Timer.hpp>
#include <List.hpp>
#include <Led.hpp>
#include <Gpio.hpp>
#include <uprintf.hpp>
#include <stdio.h>
#include <server.hpp>
#include <Esp8266Wlan.hpp>

static void rcc_setup()
{
  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}

volatile int x = 10;

 char data[65];
 size_t size = 65;

void dma2_req()
{
	dma_channel_reset(DMA1, DMA_CHANNEL5);

	dma_set_peripheral_address(DMA1, DMA_CHANNEL5, (uint32_t)&USART1_DR);
	dma_set_memory_address(DMA1, DMA_CHANNEL5, (uint32_t)data);
	dma_set_number_of_data(DMA1, DMA_CHANNEL5, size);
	dma_set_read_from_peripheral(DMA1, DMA_CHANNEL5);
	dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL5);
  dma_enable_circular_mode(DMA1, DMA_CHANNEL5);
	dma_set_peripheral_size(DMA1, DMA_CHANNEL5, DMA_CCR_PSIZE_8BIT);
	dma_set_memory_size(DMA1, DMA_CHANNEL5, DMA_CCR_MSIZE_8BIT);
	dma_set_priority(DMA1, DMA_CHANNEL5, DMA_CCR_PL_HIGH);

	dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL5);
  // dma_enable_half_transfer_interrupt(DMA1, DMA_CHANNEL5);

	dma_enable_channel(DMA1, DMA_CHANNEL5);

  usart_enable_rx_dma(USART1);
}


int main()
{
  rcc_setup();
 
  os::core::init();
  os::core::run();

  // server_init();
  // server_run();

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
  usart_enable_rx_interrupt(USART1);

  nvic_enable_irq(NVIC_USART1_IRQ);

  // -> Enable 
  usart_enable(USART1);

  nvic_set_priority(NVIC_DMA1_CHANNEL5_IRQ, 0);
	nvic_enable_irq(NVIC_DMA1_CHANNEL5_IRQ);


  dma2_req();

  while(true)
  {
    if (x == 20)
    {
      x = 1;
    }
  }
}

void usart1_isr()
{
  if (usart_get_flag(USART1, USART_FLAG_IDLE))
  {
    x = 2220;
  }
} 

void dma1_channel5_isr(void)
{
  if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_TCIF))
  {
    [[maybe_unused]] int x = 10;
    dma_clear_interrupt_flags(DMA1, DMA_CHANNEL5, DMA_TCIF);
  }

  else if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_HTIF))
  {
    [[maybe_unused]] int x = 10;
    dma_clear_interrupt_flags(DMA1, DMA_CHANNEL5, DMA_HTIF);
  }

  else if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_TEIF))
  {
    [[maybe_unused]] int x = 10;
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL5, DMA_TEIF);
  }
}