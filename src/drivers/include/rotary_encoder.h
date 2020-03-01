#pragma once 

#include <stdint.h>

// ### CONFIGURATION ### //
// - Clockwise 
#define ROTARY_ENCODER_C_PORT GPIOB
#define ROTARY_ENCODER_C_PIN  GPIO11

// - Counter clockwise 
#define ROTARY_ENCODER_CC_PORT GPIOB  
#define ROTARY_ENCODER_CC_PIN  GPIO8

// - Push button
#define ROTARY_ENCODER_BUTTON_PORT GPIOB
#define RORATY_ENCODER_BUTTON_PIN  GPIO10

// ### END CONFIGURATION ### // 

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