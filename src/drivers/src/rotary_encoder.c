#include <rotary_encoder.h>
#include <hal/exti.h>
#include <libopencm3/stm32/gpio.h>
#include <delay.h>
#include <sys_timer.h>

// TODO: add callbacks
// TODO: remove unused code 

static rotary_encoder_cb_t* callbacks[3];

#define DIR_NONE 0x0
#define DIR_CW 0x10
#define DIR_CCW 0x20

static uint8_t ttable[6][4] = {
  {0x3, 0x2, 0x1,  0x0},
  {0x3 | DIR_CCW, 0x0, 0x1, 0x0},
  {0x3 | DIR_CW, 0x2, 0x0, 0x0},
  {0x3, 0x5, 0x4, 0x0},
  {0x3, 0x3, 0x4, 0x0 | DIR_CW},
  {0x3, 0x5, 0x3, 0x0 | DIR_CCW},
};

void rotary_encoder_init() 
{
}

void rotary_encoder_set_callback(rotarty_encoder_event_t event, rotary_encoder_cb_t* cb)
{
    callbacks[event] = cb;
}

static uint8_t state = 0x00;
static int32_t counter = 0;

void rotary_encoder_handle_event(uint32_t pin, rotarty_encoder_event_t event)
{
  uint16_t cpin  = gpio_get(ROTARY_ENCODER_C_PORT, ROTARY_ENCODER_C_PIN);
  uint16_t ccpin = gpio_get(ROTARY_ENCODER_CC_PORT, ROTARY_ENCODER_CC_PIN);
  uint8_t pin_state = 0;

  if (ccpin & ROTARY_ENCODER_CC_PIN) {
    pin_state |= (1 << 1);
  }

  if (cpin & ROTARY_ENCODER_C_PIN) {
    pin_state |= 1;
  }

  state = ttable[state & 0xf][pin_state];
  uint8_t ret_state = state & 0x30;

  if (ret_state == DIR_CW) {
    counter++;
  } else if (ret_state == DIR_CCW) {
    counter--;
  }
}

int32_t rotary_encoder_get_cnt()
{
  return counter;
}