#include <Motor.hpp>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/gpio.h>

/** PWM SETUP 
void setup_motor_pwm()
{
  //Setup GPIO
  gpio_set_mode(FAN_GPIO, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, FAN_PIN);

  //Setup RCC
  rcc_periph_clock_enable(RCC_TIM1);
  rcc_periph_reset_pulse(RST_TIM1);

  //Setup Timer

  timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1,
               TIM_CR1_DIR_UP);
  timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
  timer_enable_oc_output(TIM1, TIM_OC1);
  timer_enable_break_main_output(TIM1);
  timer_set_oc_value(TIM1, TIM_OC1, 15);
  timer_set_period(TIM1, 100);
  timer_enable_counter(TIM1);
}
*/

/** EXAMPLE APPLICATION **/
/**
 * 
 void motor_callback()
{
  if (up == true)
  {
    timer_set_oc_value(TIM1, TIM_OC1, val);

    val++;
    if (val == 100)
    {
      up = false;
    }
    os::timer::create(&fan_timer, 100, motor_callback);
  }
  else if (up == false)
  {`
    timer_set_oc_value(TIM1, TIM_OC1, val);

    val--;
    if (val == 15)
    {
      up = true;
      os::timer::create(&fan_timer, 10000, motor_callback);
    }
    else
    {
      os::timer::create(&fan_timer, 100, motor_callback);
    }
  }
}

int main()
{
  setup_motor_pwm();

  os::timer::create(&fan_timer, 50, fan_timer_callback);

  while(true)
  {

  }
}





namespace drivers
{
  Motor::Motor(uint32_t pwm_timer)
    : pwm_timer_(pwm_timer) 
  {
    
  }

  void Motor::start()
  {
  }

  void Motor::soft_start()
  {

  }

  void Motor::stop()
  {

  }

  void Motor::set_thrust(uint8_t thrust)
  {
    timer.duty_cycle(60);
  }

  uint8_t Motor::get_thrust() const
  {
    return thrust_;
  }

}