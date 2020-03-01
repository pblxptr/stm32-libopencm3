#include <hal/exti.h>
#include <target.h>
#include <rotary_encoder.h>
#include <libopencm3/stm32/exti.h>

void hal_exti_isr(uint32_t pin)
{
  switch(pin) {
    case ENCODER_BUTTON_PIN:
      rotary_encoder_handle_event(pin, ROTARY_ENCODER_BUTTON_PUSH);  
      break;
    case ENCODER_CLOCKWISE_DIRECTION_PIN:
      rotary_encoder_handle_event(pin, ROTARY_ENCODER_CLOCKWISE_ROTATION);
      break;
    case ENCODER_COUNTER_CLOCKWISE_DIRECTION_PIN:
      rotary_encoder_handle_event(pin, ROTARY_ENCODER_COUNTER_CLOCKWISE_ROTATION);
      break;
    default:
      break;
    }
}