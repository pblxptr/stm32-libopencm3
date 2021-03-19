#pragma once

#include <hal/uart.hpp>
#include <drivers/uart.hpp>

#include <utils/ring_buffer.hpp>
#include <string_view>

namespace utils::debug
{
  namespace console { void print(const std::string_view); }
  #define TRACE_LVL_ERROR 0
  #define TRACE_LVL_1 1
  #define TRACE_LVL_2 2
  #define TRACE_LVL_3 3

  #ifndef TRACE_LEVEL
    #define TRACE_LEVEL TRACE1
  #endif

  #if (TRACE_LEVEL == TRACE_LVL_ERROR)
  #define TRACE_LEVEL_ERROR_ENABLED
  #endif

  #if (TRACE_LEVEL == TRACE_LVL_1)
  #define TRACE_LEVEL_ERROR_ENABLED
  #define TRACE_LEVEL_1_ENABLED
  #endif

  #if (TRACE_LEVEL == TRACE_LVL_2)
  #define TRACE_LEVEL_ERROR_ENABLED
  #define TRACE_LEVEL_1_ENABLED
  #define TRACE_LEVEL_2_ENABLED
  #endif

  #if (TRACE_LEVEL == TRACE_LVL_3)
  #define TRACE_LEVEL_ERROR_ENABLED
  #define TRACE_LEVEL_1_ENABLED
  #define TRACE_LEVEL_2_ENABLED
  #define TRACE_LEVEL_3_ENABLED
  #endif

  #ifdef TRACE_LEVEL_ERROR_ENABLED
  #define TRACE_LEVEL0(msg) console::print(msg)
  #else
  #define TRACE_LEVEL0(msg) 
  #endif

  #ifdef TRACE_LEVEL_1_ENABLED
  #define TRACE_LEVEL1(msg) console::print(msg)
  #else
  #define TRACE_LEVEL1(msg) 
  #endif

  #ifdef TRACE_LEVEL_2_ENABLED
  #define TRACE_LEVEL2(msg) console::print(msg)
  #else
  #define TRACE_LEVEL2(msg) 
  #endif

  #ifdef TRACE_LEVEL_3_ENABLED
  #define TRACE_LEVEL3(msg) console::print(msg)
  #else
  #define TRACE_LEVEL3(msg) 
  #endif

  #ifdef NDEBUG
    #define trace(lvl, msg) do {} while(0)
    #define trace_error(msg) trace(0, msg)
  #else 
    #define trace(lvl, msg) do { TRACE_LEVEL##lvl(msg); } while(0)
    #define trace_error(msg) trace(0, msg)
  #endif
}

namespace utils::debug::console
{
  void set_uart_driver(drivers::uart::UartDriver*);
  void print(const std::string_view);
  void print(const uint8_t*, size_t);
  void print(utils::containers::RingBuffer&, size_t);
  void task();
}
