extern "C" {
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>
}

#include <Os.hpp>
#include <Timer.hpp>
#include <List.hpp>
#include <Led.hpp>
#include <Gpio.hpp>
#include <uprintf.hpp>
#include <stdio.h>
#include <server.hpp>

#define FAN_GPIO GPIOA
#define FAN_PIN  GPIO8


static void rcc_setup()
{
  //Peripherals clock
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB); 
}

using utils::containers::List_t;
using drivers::Led;
using drivers::Gpio;
using os::timer::TimerHandle;


class Timer_channel 
{
  uint32_t tim_id_;
  tim_oc_id t_channel_;
public:
  Timer_channel(uint32_t tim_id, tim_oc_id t_channel)
    : tim_id_(tim_id),
      t_channel_(t_channel) 
    {
      timer_enable_oc_output(tim_id_, t_channel_);
    }

    void set_oc_mode(tim_oc_mode mode) 
    {
      timer_set_oc_mode(tim_id_, t_channel_, mode);
    }
    void set_oc_value(uint32_t oc) 
    {
      timer_set_oc_value(tim_id_, t_channel_, oc);
    }
};

class Pwm_motor
{
  Timer_channel& t_channel_;
public:
  explicit Pwm_motor(Timer_channel& t_channel) //consider Pwm_motor(timer_id, timer_channel)
    : t_channel_{t_channel}
  {
    t_channel.set_oc_mode(TIM_OCM_PWM1);
  }

  void start()
  {
    t_channel_.set_oc_value(70);
  }

  void soft_start()
  {

  }

  void stop()
  {
    t_channel_.set_oc_value(0);
  }

  void set_power(uint32_t power)
  {
    t_channel_.set_oc_value(power);
  }

};

int x = 0;
int val = 15; 

bool up = true;

void intit_timer()
{
    //Setup GPIO
  gpio_set_mode(FAN_GPIO, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, FAN_PIN);

  //Setup RCC
  rcc_periph_clock_enable(RCC_TIM1);
  rcc_periph_reset_pulse(RST_TIM1);

  //Setup Timer

  timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1,
               TIM_CR1_DIR_UP);
  timer_enable_break_main_output(TIM1);
  timer_set_period(TIM1, 100);
  timer_enable_counter(TIM1);
}


int main()
{
  rcc_setup();

  os::core::init();
  os::core::run();

  // utils::debug::uprintf_init(USART1);
  // utils::debug::uprintf_send(USART1, "Uart debug print initialized.\r\n");
  
  // intit_timer();
  // auto tchannel = Timer_channel{TIM1, TIM_OC1};
  // auto engine = Pwm_motor{tchannel};
  // engine.start();
  // engine.stop();

  server_init();

  while(true)
  {
   server_task();
  }

  // while(true)
  // {
  //   // server_check();
  //   // auto counter = timer_get_counter(TIM1);
  //   // char tab[24];

  //   // sprintf(tab, "%d\r\n", counter);
  //   // utils::debug::uprintf_send(USART1, tab);
  // }

}