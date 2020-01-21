#pragma once

#include <stdint.h>

#define RS        0
#define RW        1
#define E         2
#define BACKLIGHT 3

#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define MODE_4_BITS 0
#define MODE_8_BITS 1

#define LCD_ENTRY_MODE                 	 0x04
	#define LCD_EM_CURSOR_INCREMENT      0x02
	#define LCD_EM_CURSOR_DECREMENT      0x00
	#define LCD_EM_SHIFT_DISPLAY_DISPLAY 0x00
	#define LCD_EM_SHIFT_CURSOR          0x01

#define LCD_FUNCTION_SET 			     0x20
	#define LCD_8_BITS 					 0x10
	#define LCD_4_BITS 					 0x00
	#define LCD_1_LINE 					 0x00
	#define LCD_2_LINES 				 0x08
	#define LCD_FONT_5_8 				 0x00
	#define LCD_FONT_5_10 			     0x04

#define LCD_ON_OFF 					     0x08
	#define LCD_DISPLAY_ON 			     0x04
	#define LCD_DISPLAY_OFF 		     0x00
	#define LCD_CURSOR_ON 			     0x02
	#define LCD_CURSOR_OFF 			     0x00
	#define LCD_CURSOR_BLINK 		     0x01
	#define LCD_CURSOR_NO_BLINK          0x00

#define LCD_CLEAR 0x01
#define LCD_HOME  0x02

/* Lines to select, the value represents addresses of the lines begining */
#define LINE_1 0x00
#define LINE_2 0x40

enum backlight { BACKLIGHT_OFF, BACKLIGHT_ON };

typedef struct _hd44780_t {
  uint32_t i2cx;
  uint8_t dev_address;
  bool busy_flag;
  bool _backlight_status;
  uint8_t _payload; 
} hd44780_t;

typedef hd44780_t* hd44780_handle_t;

void hd44780_init(hd44780_handle_t handle);
void hd44780_backlight(hd44780_handle_t handle, enum backlight option);
void hd44780_display_text(hd44780_handle_t handle, char* text);
void hd44780_set_options(hd44780_handle_t handle, uint8_t options);
void hd44780_set_position(hd44780_handle_t handle, uint8_t line_nr, uint8_t position);
void hd44780_clear(hd44780_handle_t handle);
void hd44780_home(hd44780_handle_t handle);