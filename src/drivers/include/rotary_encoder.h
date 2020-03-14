#pragma once 

#include <stdint.h>
#include <target.h>

/** 
 * TODO: Push button 
 * 
 */

/* EXAMPLE OF USE
  - Setup RCC

  - Setup GPIO:   
  gpio_set_mode(ENCODER_BUTTON_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,
    ENCODER_BUTTON_PIN
  );
  gpio_set_mode(ENCODER_CLOCKWISE_DIRECTION_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,
    ENCODER_CLOCKWISE_DIRECTION_PIN
  );
  gpio_set_mode(ENCODER_COUNTER_CLOCKWISE_DIRECTION_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,
    ENCODER_COUNTER_CLOCKWISE_DIRECTION_PIN
  );

  - Setup HAL EXT: 
  hal_exti_config_t cfg;
  HAL_EXTI_INIT_STRUCT(&cfg, ENCODER_BUTTON_PORT, ENCODER_BUTTON_PIN, 
    ENCODER_BUTTON_ISR_LINE);
  hal_exti_configure(&cfg); //configure push button for encoder

  HAL_EXTI_INIT_STRUCT(&cfg, ENCODER_CLOCKWISE_DIRECTION_PORT, ENCODER_CLOCKWISE_DIRECTION_PIN, 
    ENCODER_CLOCKWISE_DIRECTION_ISR_LINE);
  hal_exti_configure(&cfg); //configure clocwise direction for encoder 

  HAL_EXTI_INIT_STRUCT(&cfg, ENCODER_COUNTER_CLOCKWISE_DIRECTION_PORT, ENCODER_COUNTER_CLOCKWISE_DIRECTION_PIN, 
    ENCODER_COUNTER_CLOCKWISE_DIRECTION_ISR_LINE);
  hal_exti_configure(&cfg); //configure counter clocwise direction for encoder 

  - Setup Encoder 
  rotary_encoder_set_callback(ROTARY_ENCODER_CLOCKWISE_ROTATION, encoder_clockwise_handle);
  rotary_encoder_set_callback(ROTARY_ENCODER_COUNTER_CLOCKWISE_ROTATION, encoder_counter_clockwise_handle);
  rotary_encoder_set_callback(ROTARY_ENCODER_BUTTON_PUSH, encoder_button_handle);
*/ 


typedef enum _rotary_encoder_event_t_ {
    ROTARY_ENCODER_CLOCKWISE_ROTATION = 0,
    ROTARY_ENCODER_COUNTER_CLOCKWISE_ROTATION,
    ROTARY_ENCODER_BUTTON_PUSH
} rotarty_encoder_event_t;

typedef void (rotary_encoder_cb_t)();

void rotary_encoder_init();
void rotary_encoder_set_callback(rotarty_encoder_event_t event, rotary_encoder_cb_t* cb);
void rotary_encoder_handle_event(uint32_t pin, rotarty_encoder_event_t event);
int32_t rotary_encoder_get_cnt();