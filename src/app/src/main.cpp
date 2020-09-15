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

int main()
{
  rcc_setup();
  
  os::core::init();
  os::core::run();

  auto esp8266 = drivers::Esp8266Wlan{
    drivers::Esp8266WlanHwCfg {
      DMA1, 
      DMA_CHANNEL5,
      NVIC_DMA1_CHANNEL5_IRQ,
      DMA_CHANNEL6,
      NVIC_DMA1_CHANNEL6_IRQ,
      USART1,
      reinterpret_cast<uint32_t>(&USART1_DR),
      NVIC_USART1_IRQ
    }
  };
  esp8266.init();
  esp8266.connect_ap("asd", "asd");

  uint8_t buff[64];

  esp8266.connect("https://wwww.wykop.pl", 80);
  esp8266.async_receive(1, buff, sizeof(buff), [](const auto ec)
  {
    if (ec == drivers::StatusCode::FAILED)
    {
      x = 12;
    }
  });

  while(true)
  {

  }
}
