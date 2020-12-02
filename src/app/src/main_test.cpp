extern "C" {
  #include <libopencm3/stm32/rcc.h>
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/cm3/systick.h>
  #include <libopencm3/stm32/timer.h>
  #include <libopencm3/cm3/nvic.h>
  #include <libopencm3/stm32/usart.h>
  #include <libopencm3/stm32/dma.h>
}

static void rcc_setup()
{
  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}

#define __IO volatile

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
    __IO uint32_t tmpreg;
    tmpreg = USART1_SR;
    (void) tmpreg;
    tmpreg = USART1_DR;
    (void) tmpreg;

}

int main()
{
  rcc_setup();
  
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(8999);

  systick_interrupt_enable();
  systick_counter_enable();

  rcc_periph_clock_enable(RCC_USART1);
  rcc_periph_clock_enable(RCC_DMA1);

  // -> GPIO
  gpio_set_mode(GPIO_BANK_USART1_TX, GPIO_MODE_OUTPUT_50_MHZ, 
    GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

  gpio_set_mode(GPIO_BANK_USART1_RX, GPIO_MODE_INPUT, 
    GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, GPIO_USART1_RX);

  // -> Configuration
  usart_set_mode(USART1, USART_MODE_TX_RX);
  usart_set_baudrate(USART1, 115200);
  usart_set_parity(USART1, USART_PARITY_NONE);
  usart_set_databits(USART1, 8);
  usart_set_stopbits(USART1, 1);
  usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

  // usart_enable_rx_interrupt(USART1);

  // usart_clear_idle_flag(USART1);

  // for (uint32_t i = 0; i < 9999999; i++)
  // {
  //   __asm("nop");
  // }
  



  for (uint32_t i = 0; i < 9999999; i++)
  {
    __asm("nop");
  }
  
  nvic_enable_irq(NVIC_USART1_IRQ);

  // -> Enable 
  usart_enable(USART1);

  for (uint32_t i = 0; i < 9999999; i++)
  {
    __asm("nop");
  }
  
  usart_enable_idle_interrupt(USART1);

  while(true)
  {
    __asm("nop");
  }
}




static volatile int x = 0;
static volatile int y = 0;

bool is_enabled()
{
  return USART1_CR1 & USART_CR1_IDLEIE;
}

bool is_set()
{
  return USART1_SR & USART_SR_IDLE;
}

void usart1_isr()
{
  if(is_enabled() && is_set())
  {
      __IO uint32_t tmpreg;
      tmpreg = USART1_SR;
      (void) tmpreg;
      tmpreg = USART1_DR;
      (void) tmpreg;

      x++;
  }
}
  

  // if (((USART_CR1(USART1) & USART_CR1_RXNEIE) != 0) && ((USART_SR(USART1) & USART_FLAG_RXNE) != 0))
  // {
  //   [[maybe_unused]] auto y = USART1_SR;
  //   [[maybe_unused]] auto x = USART1_DR;

  //   usart_disable_rx_interrupt(USART1);
  //   usart_enable_idle_interrupt(USART1);
  // }

  // else if (((USART_CR1(USART1) & USART_CR1_IDLEIE) != 0) && ((USART_SR(USART1) & USART_FLAG_IDLE) != 0))
  // {
  //   [[maybe_unused]] auto y = USART1_SR;
  //   [[maybe_unused]] auto x = USART1_DR;

  //   usart_enable_rx_interrupt(USART1);
  //   usart_disable_idle_interrupt(USART1);
  // }
