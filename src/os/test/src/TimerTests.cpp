#include <gtest/gtest.h>

#include <Timer.hpp>
#include <private/PrivateTimer.hpp>
#include <iostream>

using namespace os::timer;

static uint32_t callback_shared_resource = 0;

void callback1()
{
  callback_shared_resource = 1000;
}

void callback2()
{
  callback_shared_resource = 2000;
}

void callback3()
{
  callback_shared_resource = 3000;
}

class TimerTests : public ::testing::Test
{};

TEST_F(TimerTests, WhenAddingMultipleTimersThenTheyShouldBeSortedByTimeout)
{
  //Arrange
  TimerHandle t1;
  TimerHandle t2;
  TimerHandle t3; 

  //Act
  os::timer::create(&t1, 1000, callback1);
  os::timer::create(&t2, 2000, callback2);
  os::timer::create(&t3, 3000, callback3);

  //Assert
  for(size_t i = 0; i < 1000; i++) 
    os::timer::check_timers();
  ASSERT_EQ(callback_shared_resource, 1000);

  for(size_t i = 0; i < 1000; i++) 
    os::timer::check_timers();
  ASSERT_EQ(callback_shared_resource, 2000);

  for(size_t i = 0; i < 1000; i++) 
    os::timer::check_timers();
  ASSERT_EQ(callback_shared_resource, 3000);
}

static TimerHandle t1;
static TimerHandle t2;


void cb1()
{
  os::timer::create(&t1, 5000, cb1);
  std::cout << "cb1\n";
}


TEST_F(TimerTests, WhenCreatingTimerFromIsrThenItShouldntBreakTheList)
{
  os::timer::create(&t1, 5000, cb1);

  for (size_t i = 0; i < 10000; i++)
  {
    os::timer::check_timers();
  }
}