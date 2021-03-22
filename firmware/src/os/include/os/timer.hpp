#pragma once

#include <chrono>
#include <functional>
#include <type_traits>

#include <utils/list.hpp>

namespace os::timer
{
  using timeout_cb_t = std::add_pointer<void()>::type;
  using ticks_t = uint32_t;

  struct Timer
  {
    ticks_t timeout;
    timeout_cb_t cb;
    utils::containers::List node;
  };

  //Public
  void request_timer(Timer*, const std::chrono::milliseconds&, timeout_cb_t);
  void request_timer(Timer*, const std::chrono::seconds&, timeout_cb_t);
  void request_timer(Timer*, const std::chrono::minutes&, timeout_cb_t);
}
