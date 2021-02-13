#pragma once

#include <chrono>
#include <functional>

namespace os::timer
{
  using timeout_cb_t = void (*)();

  struct Timer;

  void request_timer(Timer*, const std::chrono::milliseconds&, timeout_cb_t*);
  void request_timer(Timer*, const std::chrono::seconds&, timeout_cb_t*);
  void request_timer(Timer*, const std::chrono::minutes&, timeout_cb_t*);
}
