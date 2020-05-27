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

  Dummy d3{};
  d3.x = 40;

  List_t l{};
  l.append(make_link_ptr(d1));
  l.append(make_link_ptr(d2));
  l.append(make_link_ptr(d3));

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