#include <os/timer.hpp>
#include <os/internal/timer_internal.hpp>

#include <gtest/gtest.h>

using namespace os::timer;

namespace {
  int value_modified_by_callback = 0;

  void call_timers_notify_tick(size_t n)
  {
    for (size_t i = 0; i < n; i++)
    {
      os::timer::notify_tick();
    }
  }
}

struct TimerTest : public ::testing::Test
{
  void SetUp()
  {
    value_modified_by_callback = false;
  }
};

TEST_F(TimerTest, WhenRequestingATimerThenItShouldBeFiredAfterItIsExpired)
{
  //Arrange
  auto timer = Timer{};
  const int expected_value_modified_by_callback = 1000;
  auto cb = []() { value_modified_by_callback = 1000; };
  const auto timeout = std::chrono::milliseconds(1000);

  //Act
  os::timer::request_timer(&timer, timeout, cb);
  call_timers_notify_tick(timeout.count());

  //Assert
  ASSERT_EQ(value_modified_by_callback, expected_value_modified_by_callback);
}

TEST_F(TimerTest, WhenRequestingMultipleTimersThenTheyShouldBeFiredAccordinglyToTheirTimeout)
{
  //Arrange
  auto t1 = Timer{};
  const auto t1_timeout = std::chrono::milliseconds(1000);
  const int t1_expected_cb_value = 1000;
  const auto t1_cb = []() { value_modified_by_callback = 1000; };

  auto t2 = Timer{};
  const auto t2_timeout = std::chrono::milliseconds(2000);
  const int t2_expected_cb_value = 2000;
  const auto t2_cb = []() { value_modified_by_callback = 2000; };

  //Act
  os::timer::request_timer(&t2, t2_timeout, t2_cb);
  os::timer::request_timer(&t1, t1_timeout, t1_cb);

  call_timers_notify_tick(t1_timeout.count());
  const int t1_cb_actual_value = value_modified_by_callback;

  call_timers_notify_tick(t2_timeout.count());
  const int t2_cb_actual_value = value_modified_by_callback;

  //Assert
  ASSERT_EQ(t1_cb_actual_value, t1_expected_cb_value);
  ASSERT_EQ(t2_cb_actual_value, t2_expected_cb_value);
}