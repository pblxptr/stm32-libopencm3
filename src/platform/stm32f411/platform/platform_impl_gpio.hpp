extern "C" {
  #include <libopencm3/stm32/gpio.h>
}

namespace platform::gpio
{
  constexpr drivers::gpio::Gpio_cfg gpios[] = {
    {
      GPIOA,
      GPIO1
    }
  };
}