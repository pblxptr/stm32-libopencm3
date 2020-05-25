extern "C" {
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
}

#include <Os.hpp>
#include <List.hpp>

static void rcc_setup()
{
  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}

using namespace utils::containers;

struct Timer 
{
  int x;
  ListNode_t node;
};

int main()
{
  os::core::init();
  os::core::run();

  auto t1 = Timer{};
  t1.x = 20;
  auto t2 = Timer{};
  t2.x = 30;
  List_t timers_list{};
  timers_list.append(&t1.node);
  timers_list.append(&t2.node);

  auto it = timers_list.begin();

  timers_list.erase(it);


  volatile int xd = 20;

  for (ListNode_t& x : timers_list)
  {
    Timer* t = container_of(&x, Timer, node);

    if (t->x == 30)
    {
      xd += 30;
    }
  }

  while(1)
  {
    int x = 20;
  }
}