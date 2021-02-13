#include <drivers/gpio.hpp>
#include <cstddef>
extern "C" {
  #include <libopencm3/stm32/gpio.h>
}

using namespace drivers::gpio;

namespace {
}

namespace platform::ll_drivers::gpio
{
  GpioDriver gpios[] = {
    {GPIOA, GPIO0}, // -> 0
    {GPIOA, GPIO1}, // -> 1
    {GPIOA, GPIO2}, // -> 2
    {GPIOA, GPIO3}, // -> 3
    {GPIOA, GPIO4}, // -> 4
    {GPIOA, GPIO5}, // -> 5
    {GPIOA, GPIO6}, // -> 6
    {GPIOA, GPIO7}, // -> 7
    {GPIOA, GPIO8}, // -> 8
    {GPIOA, GPIO9}, // -> 9
    {GPIOA, GPIO10}, // -> 10
    {GPIOA, GPIO11}, // -> 11
    {GPIOA, GPIO12}, // -> 12
    {GPIOA, GPIO13}, // -> 13
    {GPIOA, GPIO14}, // -> 14
    {GPIOA, GPIO15}, // -> 15
    //16-31
    {GPIOB, GPIO0}, // -> 16
    {GPIOB, GPIO1}, // -> 17
    {GPIOB, GPIO2}, // -> 18
    {GPIOB, GPIO3}, // -> 19
    {GPIOB, GPIO4}, // -> 20
    {GPIOB, GPIO5}, // -> 21
    {GPIOB, GPIO6}, // -> 22
    {GPIOB, GPIO7}, // -> 23
    {GPIOB, GPIO8}, // -> 24
    {GPIOB, GPIO9}, // -> 25
    {GPIOB, GPIO10}, // -> 26
    {GPIOB, GPIO11}, // -> 27
    {GPIOB, GPIO12}, // -> 28
    {GPIOB, GPIO13}, // -> 29
    {GPIOB, GPIO14}, // -> 30
    {GPIOB, GPIO15}, // -> 31
    //32-47
    {GPIOC, GPIO0}, // -> 32
    {GPIOC, GPIO1}, // -> 33
    {GPIOC, GPIO2}, // -> 34
    {GPIOC, GPIO3}, // -> 35
    {GPIOC, GPIO4}, // -> 36
    {GPIOC, GPIO5}, // -> 37
    {GPIOC, GPIO6}, // -> 38
    {GPIOC, GPIO7}, // -> 39
    {GPIOC, GPIO8}, // -> 40
    {GPIOC, GPIO9}, // -> 41
    {GPIOC, GPIO10}, // -> 42
    {GPIOC, GPIO11}, // -> 43
    {GPIOC, GPIO12}, // -> 44
    {GPIOC, GPIO13}, // -> 45
    {GPIOC, GPIO14}, // -> 46
    {GPIOC, GPIO15}  // -> 47
  };
}