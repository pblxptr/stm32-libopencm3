#pragma once

#include <chrono>
#include <functional>
#include <type_traits>

#include <utils/list.hpp>

namespace os::timer
{
  using timeout_cb_t = std::add_pointer<void()>::type;
  using ticks_t = uint32_t;
  using delay_t = std::chrono::milliseconds;

  struct Timer
  {
    ticks_t timeout;
    timeout_cb_t cb;
    utils::containers::List node;
  };

  template<class T>

  //Public
  delay_t to_delay(const T& time) { return std::chrono::duration_cast<std::chrono::milliseconds>(time); }
  void request_timer(Timer*, const delay_t&, timeout_cb_t);
  void wait(const delay_t&);
}
