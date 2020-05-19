#include <led.h>
#include <libopencm3/stm32/gpio.h>

void led_init(led_handle_t led)
{   
  gpio_set_mode(led->gpiox, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, led->pin_mask);
  led_set_state(led, LED_STATE_OFF);
}

void led_set_state(led_handle_t led, led_state_t state)
{ 
  if ((int)led->active_on == (int)state) {
    gpio_set(led->gpiox, led->pin_mask);
  } else {
    gpio_clear(led->gpiox, led->pin_mask);
  }
}

void led_toggle(led_handle_t led)
{
  gpio_toggle(led->gpiox, led->pin_mask);
}