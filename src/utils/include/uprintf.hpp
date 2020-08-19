#pragma once

#include <stdint.h>

namespace utils::debug 
{
  void uprintf_init(uint32_t usart);
  void uprintf_send(uint32_t usart, const char* data);
  void uprintf_send(uint32_t usart, const uint8_t data); 
}
