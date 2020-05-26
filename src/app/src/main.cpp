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


struct Dummy
{
  int x;
  ListNode_t node;
};

int main()
{
  os::core::init();
  os::core::run();

  Dummy d1{};
  d1.x = 20;

  Dummy d2{};
  d2.x = 30;

  List_t l{};
  l.append(node_link(d1));
  l.append(node_link(d2));

  volatile int dx;

  while(1)
  {
    for(auto& x : l)
    {
      Dummy* ptr = container_of(&x, Dummy, node);
      
      if (dx == 10)
      {
        ptr->x = 30;
      }
    }
  }
}