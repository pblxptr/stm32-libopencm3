#include <drivers/gpio.hpp>
#include <hal/gpio.hpp>
#include <drivers/uart.hpp>
#include <hal/uart.hpp>
#include <platform/config.hpp>
#include <platform/peripherals.hpp>


#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))

volatile int x = 10;

drivers::gpio::GpioDriver* blue_led_driver{nullptr};
drivers::gpio::GpioDriver* red_led1_driver{nullptr};
drivers::gpio::GpioDriver* red_led2_driver{nullptr};
drivers::gpio::GpioDriver* red_led3_driver{nullptr};

drivers::uart::UartDriver* driver{nullptr};

void rx_completed([[maybe_unused]]drivers::uart::UartDriver* driver)
{
  hal::gpio::toggle(red_led1_driver); //when tc
}

void rx_ended([[maybe_unused]]drivers::uart::UartDriver* driver)
{
  hal::gpio::toggle(red_led2_driver); //when idle
}

void rx_char_received([[maybe_unused]]drivers::uart::UartDriver* driver)
{
  hal::gpio::toggle(red_led3_driver); //when single character is received
}

extern "C"
  void usart1_isr()
  {

  }

int main()
{
    rcc_periph_clock_enable(RCC_USART1);
    rcc_periph_clock_enable(RCC_DMA2);
    rcc_periph_clock_enable(RCC_GPIOA);

    //Enable nvic interrupt for dma stream
    nvic_enable_irq(NVIC_DMA2_STREAM2_IRQ);
    nvic_enable_irq(NVIC_USART1_IRQ);

    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);
	  gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);
    
    usart_set_mode(USART1, USART_MODE_TX_RX);
    usart_set_baudrate(USART1, 9600);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, 1);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
    usart_enable_rx_dma(USART1);
    usart_enable_rx_interrupt(USART1);
    usart_enable(USART1);


    char buff[64];
    uint32_t s = 64;

    //Configure dma
    dma_disable_stream(DMA2, DMA_STREAM2);
    dma_stream_reset(DMA2, DMA_STREAM2);
    dma_set_peripheral_address(DMA2, DMA_STREAM2, (uint32_t) &USART1_DR);
    dma_channel_select(DMA2, DMA_STREAM2, DMA_SxCR_CHSEL_4);
    dma_set_priority(DMA2, DMA_STREAM2, DMA_SxCR_PL_MEDIUM);
    dma_set_memory_size(DMA2, DMA_STREAM2, DMA_SxCR_MSIZE_8BIT);
    dma_set_peripheral_size(DMA2, DMA_STREAM2, DMA_SxCR_PSIZE_8BIT);
    dma_enable_memory_increment_mode(DMA2, DMA_STREAM2);
    dma_enable_circular_mode(DMA2, DMA_STREAM2);
    dma_set_transfer_mode(DMA2, DMA_STREAM2, DMA_SxCR_DIR_PERIPHERAL_TO_MEM);
    
    dma_set_memory_address(DMA2, DMA_STREAM2, (uint32_t) buff);
    dma_set_number_of_data(DMA2, DMA_STREAM2, s);
    dma_enable_transfer_complete_interrupt(DMA2, DMA_STREAM2);

    dma_enable_stream(DMA2, DMA_STREAM2);


  // constexpr auto blue_led_config = drivers::gpio::GpioDriverConfig<
  //   platform::config::BLUE_LED_GPIO,
  //   drivers::gpio::Mode::OUTPUT,
  //   drivers::gpio::PullUpDown::PULLUP
  // >{};

  // constexpr auto red_led1_config = drivers::gpio::GpioDriverConfig<
  //   platform::config::RED_LED1_GPIO,
  //   drivers::gpio::Mode::OUTPUT,
  //   drivers::gpio::PullUpDown::PULLUP
  // >{};

  // constexpr auto red_led2_config = drivers::gpio::GpioDriverConfig<
  //   platform::config::RED_LED2_GPIO,
  //   drivers::gpio::Mode::OUTPUT,
  //   drivers::gpio::PullUpDown::PULLUP
  // >{};

  // constexpr auto red_led3_config = drivers::gpio::GpioDriverConfig<
  //   platform::config::RED_LED3_GPIO,
  //   drivers::gpio::Mode::OUTPUT,
  //   drivers::gpio::PullUpDown::PULLUP
  // >{};

  // hal::gpio::init();
  // blue_led_driver = hal::gpio::setup<decltype(blue_led_config)>();
  // red_led1_driver = hal::gpio::setup<decltype(red_led1_config)>();
  // red_led2_driver = hal::gpio::setup<decltype(red_led2_config)>();
  // red_led3_driver = hal::gpio::setup<decltype(red_led3_config)>();

  // hal::gpio::set(blue_led_driver);
  // hal::gpio::set(red_led1_driver);
  // hal::gpio::set(red_led2_driver);
  // hal::gpio::set(red_led3_driver);


  // //UAR
  // constexpr auto serial1_config = drivers::uart::UartDriverConfig<
  //   platform::config::SERIAL1,
  //   drivers::uart::Mode::RX_TX,
  //   drivers::uart::Baudrate::B_9600,
  //   drivers::uart::DataBits::D_8,
  //   drivers::uart::StopBits::S_1,
  //   drivers::uart::Parity::NONE,
  //   drivers::uart::FlowControl::NONE
  // >{};

  // uint8_t buffer[128];
  // const size_t buffer_size = ARRAY_LEN(buffer);

  // // //Init & setup
  // hal::uart::init();
  // driver = hal::uart::setup<decltype(serial1_config)>();
  // // driver->rx_completed_cb = rx_completed;
  // // driver->rx_end_cb = rx_ended;
  // driver->rx_char_received_cb = rx_char_received;
  
  // hal::uart::receive(driver, buffer, buffer_size);

  while(1)
  {
    if (x == 20)
    {
      x = 10;
    }
  }
}