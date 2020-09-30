#include <Gpio.hpp>

extern "C" {
#include <libopencm3/stm32/gpio.h>
}


// namespace drivers
// {
//   Gpio::Gpio(uint32_t gpiox, uint32_t pin)
//     : gpiox_(gpiox),
//       pin_(pin)
//     {
//       gpio_set_mode(gpiox_, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, pin_);
//       gpio_clear(gpiox_, pin_);
//     }
  
//   void Gpio::set()
//   {
//     gpio_set(gpiox_, pin_);
//   }

//   void Gpio::clear()
//   {
//     gpio_clear(gpiox_, pin_);
//   }

//   void Gpio::toggle()
//   {
//     gpio_toggle(gpiox_, pin_);
//   }
// }