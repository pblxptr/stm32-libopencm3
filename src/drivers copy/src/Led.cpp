extern "C" {
#include <libopencm3/stm32/gpio.h>
}

#include <type_traits>
#include <Led.hpp>

// namespace drivers { 

// Led::Led(uint32_t gpiox, uint32_t pin, ActiveOn active_on)
//   : gpiox_{gpiox}, pin_{pin}, active_on_{active_on}
//     {
//       gpio_set_mode(gpiox_, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, pin_);
//       set_state(State::OFF);
//     }

// void Led::toggle()
// {
//   gpio_toggle(gpiox_, pin_);
// }

// void Led::set_state(Led::State state)
// {
//   if (static_cast<std::underlying_type_t<ActiveOn>>(active_on_) 
//    == static_cast<std::underlying_type_t<State>>(state)) 
//   {
//     gpio_set(gpiox_, pin_);
//   } 
//   else 
//   {
//     gpio_clear(gpiox_, pin_);
//   }
// }

// } //namespace drivers
