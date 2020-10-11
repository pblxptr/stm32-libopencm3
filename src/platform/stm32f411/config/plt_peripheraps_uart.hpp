#pragma once

extern "C" {
  #include <libopencm3/stm32/usart.h>
}

// namespace {
// constexpr uint32_t UARTS[] = {
//   USART1,
//   USART2,
//   USART3,
//   UART4
// };

// }

// namespace platform::peripherals::uart
// {
//   constexpr auto uarts() 
//   {
//     return UARTS;
//   }

//   constexpr auto uarts_num()
//   {
//     return sizeof(UARTS) / sizeof(UARTS[0]);
//   }
// }