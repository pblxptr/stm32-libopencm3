extern "C" {
  #include <libopencm3/stm32/usart.h> 
  #include <libopencm3/stm32/gpio.h>
  #include <libopencm3/stm32/rcc.h>
  #include <libopencm3/cm3/nvic.h>
}

#include <server.hpp>
#include <stdint.h>
#include <ring_buffer.hpp>
#include <Os.hpp>
#include <Timer.hpp>
#include <target.h>

static uint8_t w_buffer[1024]; // write buffer
static uint8_t r_buffer[1024]; // read buffer

utils::containers::RingBuffer write_rb{w_buffer, sizeof(w_buffer)};
utils::containers::RingBuffer read_rb{r_buffer, sizeof(r_buffer)};

static void sendData()
{
  if (write_rb.capacity() != 0)
  {
    usart_send(USART1, write_rb.read());
    usart_enable_tx_interrupt(USART1);
  }
  else 
  {
    usart_disable_tx_interrupt(USART1);
  }
}

static void readData()
{
  auto data = usart_recv(USART1);
  read_rb.write(static_cast<uint8_t>(data));

  // usart_enable_rx_interrupt(USART1);
}

void server_init()
{
  //RCC
  rcc_periph_clock_enable(RCC_USART1);

  //GPIO
  gpio_set_mode(GPIO_BANK_USART1_TX, GPIO_MODE_OUTPUT_50_MHZ, 
    GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

  gpio_set_mode(GPIO_BANK_USART1_RX, GPIO_MODE_INPUT, 
    GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, GPIO_USART1_RX);

  //USART
  usart_set_mode(USART1, USART_MODE_TX_RX);
  usart_set_baudrate(USART1, 9600);
  usart_set_parity(USART1, USART_PARITY_NONE);
  usart_set_databits(USART1, 8);
  usart_set_stopbits(USART1, 1);
  usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
  usart_enable_rx_interrupt(USART1);

  //ISR
  nvic_enable_irq(NVIC_USART1_IRQ);
  
  //Enable 
  usart_enable(USART1);
}

void server_task()
{
    if (read_rb.capacity() >= 64)
    {
      while (read_rb.capacity() != 0)
      {
        write_rb.write(read_rb.read());
      }
      sendData();
    }
}

void usart1_isr()
{
  if (usart_get_flag(USART1, USART_FLAG_TXE) != 0) 
  {
    sendData();
  }

  if (usart_get_flag(USART1, USART_FLAG_RXNE) != 0) // when data is ready to read
  {
    readData(); 
  }
} 