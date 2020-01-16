#include <stdbool.h>
#include <hd44780.h>
#include <libopencm3/stm32/i2c.h>

enum backlight backlight_status = BACKLIGHT_ON;
bool use_busy_flag = false;

static uint8_t lcd_payload = 0x00;

//PRIVATE FUNCTIONS DECLARATIONS AND INLINE IMPLEMENTATIONS 
static bool __is_busy();
static void __set_payload_data(uint8_t data);
static void __lcd_write_instruction(uint8_t command);

inline static void __send_payload(hd44780_handle_t handle)
{
    i2c_send_start(handle->i2cx);
    i2c_send_7bit_address(handle->i2cx, handle->dev_address, I2C_READ);
    i2c_send_data(handle->i2cx, lcd_payload);
    i2c_send_stop(handle->i2cx);
}

inline static void __set_payload_e_hi()
{
	lcd_payload |= (1 << E);
}

inline static void __set_payload_e_lo()
{
	lcd_payload &= (~(1 << E));
}

inline static void __set_payload_rs_hi()
{
	lcd_payload |= (1 << RS);
}

inline static void __set_payload_rs_lo()
{
	lcd_payload &= (~(1 << RS));
}

inline static void __set_payload_rw_hi()
{
	lcd_payload |= (1 << RW);
}

inline static void __set_payload_rw_lo()
{
	lcd_payload &= (~(1 << RW));
}

bool __is_busy()
{
	// // It should works but in need to be checked. 
	// // At this moment the busy flag read is disabled 
	// /* Set RW */
	// __set_payload_data(0);

	// __set_payload_rw_hi();
	// __send_payload();
	// /* From now RW is 1 */

	// // /* Read first nibble */
	// __set_payload_e_hi();
	// __send_payload();

	//   // uint8_t x1 = twi_read_byte(SLA, NO_ACK); // first nibble

	// __set_payload_e_lo();
	// __send_payload();
	// /* Read first nibble done */

	// /* Read second nibble */
	// __set_payload_e_hi();
	// __send_payload();

	// // uint8_t x2 = twi_read_byte(SLA, NO_ACK); //second nibble

	// __set_payload_e_lo();
	// __send_payload();
	// /* Read second nibble done */

	// __set_payload_rw_lo();
	// __send_payload();

	// /* From now RW is 0 */

 

	// return false; // flag shoud be checked
}

static void __set_payload_data(uint8_t data)
{
	//Reset only data bits
	lcd_payload &= ~(1 << D4);
	lcd_payload &= ~(1 << D5);
	lcd_payload &= ~(1 << D6);
	lcd_payload &= ~(1 << D7);

    if (data & 0x01) lcd_payload |= (1 << D4);
    if (data & 0x02) lcd_payload |= (1 << D5);
    if (data & 0x04) lcd_payload |= (1 << D6);
    if (data & 0x08) lcd_payload |= (1 << D7);
    if (backlight_status == BACKLIGHT_ON) {
		lcd_payload |= (1 << BACKLIGHT);
	}
}

inline static void __clear_all()
{
	__set_payload_data(0);
	__set_payload_e_lo();
	__set_payload_rs_lo();
	__set_payload_rw_lo();
}

void lcd_init(hd44780_handle_t handle)
{
	//Initialization start
	_delay_ms(100); //wait

	for (int i = 0; i < 3; i++) {
		__set_payload_data(0x03);

		__set_payload_e_hi(); // E -> 1
		__send_payload();

		__set_payload_e_lo(); // E -> 0
		__send_payload();

		// _delay_ms(10);
	}

	//Set data interface to 4 bits
	__set_payload_data(0x02);

	__set_payload_e_hi();
	__send_payload();

	__set_payload_e_lo();
	__send_payload();

	//4 bits interface enabled. Now we can use high level functions like lcd_write_command, etc...

	//Function set
	__lcd_write_instruction(LCD_FUNCTION_SET | LCD_4_BITS | LCD_2_LINES | LCD_FONT_5_8);

	//Display off
	__lcd_write_instruction(LCD_ON_OFF | LCD_DISPLAY_OFF | LCD_CURSOR_OFF | LCD_CURSOR_NO_BLINK);

	//Display clear
	__lcd_write_instruction(LCD_CLEAR);

	//Entry mode
	__lcd_write_instruction(LCD_ENTRY_MODE | LCD_EM_CURSOR_INCREMENT);

	//Initialization done.

	//////////---------------------////////////////////
	__lcd_write_instruction(LCD_ON_OFF | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_CURSOR_BLINK);
}

void lcd_backlight(enum backlight status) 
{
	backlight_status = status;
}

void lcd_display_text(char* text)
{
	while(*(text)) {
		lcd_write_char(*text);
		++text;
	}
}

void lcd_set_options(uint8_t options)
{
	__lcd_write_instruction(LCD_ON_OFF | options);
}

void lcd_set_position(uint8_t line_nr, uint8_t position)
{
	uint8_t data = 0;

	if (line_nr == LINE_1) {
		data = LINE_1;
	} else {
		data = LINE_2;
	}
	data += position;
	data |= (1 << D7);

	__lcd_write_instruction(data);
}

void lcd_clear()
{
	__lcd_write_instruction(LCD_CLEAR);
}

void lcd_home()
{
	__lcd_write_instruction(LCD_HOME);
}

//PIVATE FUNCTIONS IMPLEMENTATION
void __lcd_write_instruction(uint8_t command)
{
	//Send first nibble
	__set_payload_data((command & 0xF0) >> 4);
	__set_payload_e_hi();
	__send_payload();
	__set_payload_e_lo();
	__send_payload();

	//Send second nibble
	__set_payload_data(command & 0x0F);
	__set_payload_e_hi();
	__send_payload();
	__set_payload_e_lo();
	__send_payload();

	__clear_all();
	__send_payload();

		if (use_busy_flag) {
		while (__is_busy());
	} else {
		// _delay_ms(10);
	}

}

static void lcd_write_char(uint8_t c)
{
	__set_payload_rs_hi();
	__lcd_write_instruction(c);
	__set_payload_rs_lo();
}