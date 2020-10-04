// #pragma once

// extern "C" {
//   #include <libopencm3/stm32/gpio.h>
//   #include <libopencm3/stm32/rcc.h>
// }

// #include <drivers/gpio.hpp>

// namespace {
//   auto convert_mode(const drivers::gpio::Mode& mode)
//   {
//     switch(mode)
//     {
//       case drivers::gpio::Mode::INPUT:
//         return GPIO_MODE_INPUT;

//       case drivers::gpio::Mode::OUTPUT:
//         return GPIO_MODE_OUTPUT;

//       case drivers::gpio::Mode::ANALOG:
//         return GPIO_MODE_ANALOG;

//       case drivers::gpio::Mode::AF:
//         return GPIO_MODE_AF;
//     }
//     return GPIO_MODE_INPUT;
//   }

//   auto convert_plup_pldown(const drivers::gpio::PullUpDown& puppd)
//   {
//     switch (puppd)
//     {
//       case drivers::gpio::PullUpDown::NONE:
//         return GPIO_PUPD_NONE;

//       case drivers::gpio::PullUpDown::PULLDOWN:
//         return GPIO_PUPD_PULLDOWN;
      
//       case drivers::gpio::PullUpDown::PULLUP:
//         return GPIO_PUPD_PULLUP;
//     }

//     return GPIO_PUPD_NONE;
//   }
// }

// namespace platform::hal::gpio
// {
//   inline void init()
//   {
//     rcc_periph_clock_enable(RCC_GPIOA);
//     rcc_periph_clock_enable(RCC_GPIOB);
//     rcc_periph_clock_enable(RCC_GPIOC);
//     rcc_periph_clock_enable(RCC_GPIOD);
//   }

//   void setup(const drivers::gpio::GpioDriver& gpio)
//   {
//     const auto mode = convert_mode(gpio.mode);
//     const auto pd = convert_plup_pldown(gpio.pd); 

//     gpio_mode_setup(gpio.pinout.port, mode, pd, gpio.pinout.pin);
//   }

//   void set(const drivers::gpio::GpioDriver& gpio)
//   {
//     gpio_set(gpio.pinout.port, gpio.pinout.pin);
//   }

//   void clear(const drivers::gpio::GpioDriver& gpio)
//   {
//     gpio_clear(gpio.pinout.port, gpio.pinout.pin);
//   }
// }