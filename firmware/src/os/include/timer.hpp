#pragma once

#include <chrono>
#include <functional>

#include <list.hpp>

namespace os::timer
{
  using timeout_cb_t = void (*)();
  using ticks_t = uint32_t;

  struct Timer
  {
    ticks_t timeout;
    timeout_cb_t cb;
    os::utils::List list;
  };

  //Public
  void request_timer(Timer*, const std::chrono::milliseconds&, timeout_cb_t*);
  void request_timer(Timer*, const std::chrono::seconds&, timeout_cb_t*);
  void request_timer(Timer*, const std::chrono::minutes&, timeout_cb_t*);
}
