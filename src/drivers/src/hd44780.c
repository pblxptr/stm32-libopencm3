#include <stdbool.h>
#include <hd44780.h>
#include <libopencm3/stm32/i2c.h>
#include <delay.h>

//TODO: Refactor needed -> a lot of unnescesery function calls.

//PRIVATE FUNCTIONS DECLARATIONS AND INLINE IMPLEMENTATIONS 
static bool __is_busy();
static void __set_payload_data(hd44780_handle_t handle, uint8_t data);
static void __hd44780_write_instruction(hd44780_handle_t handle, uint8_t command);
static void __hd44780_write_char(hd44780_handle_t handle, char c);

inline static void __send_payload(hd44780_handle_t handle)
{
	uint32_t reg32 __attribute__((unused));

    i2c_send_start(handle->i2cx);

	while (!((I2C_SR1(handle->i2cx) & I2C_SR1_SB)
		& (I2C_SR2(handle->i2cx) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(handle->i2cx, handle->dev_address, I2C_WRITE);
	while (!(I2C_SR1(handle->i2cx) & I2C_SR1_ADDR));

	reg32 = I2C_SR2(handle->i2cx);

    i2c_send_data(handle->i2cx, handle->_payload);

	while (!(I2C_SR1(handle->i2cx) & (I2C_SR1_BTF | I2C_SR1_TxE)));

    i2c_send_stop(handle->i2cx);
}

inline static void __set_payload_e_hi(hd44780_handle_t handle)
{
	handle->_payload |= (1 << E);
}

inline static void __set_payload_e_lo(hd44780_handle_t handle)
{
	handle->_payload &= (~(1 << E));
}

inline static void __set_payload_rs_hi(hd44780_handle_t handle)
{
	handle->_payload |= (1 << RS);
}

inline static void __set_payload_rs_lo(hd44780_handle_t handle)
{
	handle->_payload &= (~(1 << RS));
}

inline static void __set_payload_rw_hi(hd44780_handle_t handle)
{
	handle->_payload |= (1 << RW);
}

inline static void __set_payload_rw_lo(hd44780_handle_t handle)
{
	handle->_payload &= (~(1 << RW));
}

//Not implemented
bool __is_busy()
{

}

static void __set_payload_data(hd44780_handle_t handle, uint8_t data)
{
	//Reset only data bits
	handle->_payload &= ~(1 << D4);
	handle->_payload &= ~(1 << D5);
	handle->_payload &= ~(1 << D6);
	handle->_payload &= ~(1 << D7);

    if (data & 0x01) handle->_payload |= (1 << D4);
    if (data & 0x02) handle->_payload |= (1 << D5);
    if (data & 0x04) handle->_payload |= (1 << D6);
    if (data & 0x08) handle->_payload |= (1 << D7);
    if (handle->_backlight_status == BACKLIGHT_ON) {
		handle->_payload |= (1 << BACKLIGHT);
	}
}

inline static void __clear_all(hd44780_handle_t handle)
{
	__set_payload_data(handle, 0);
	__set_payload_e_lo(handle);
	__set_payload_rs_lo(handle);
	__set_payload_rw_lo(handle);
}

void hd44780_init(hd44780_handle_t handle)
{
	//Initialization start
	delay_ms(100); //wait

	for (int i = 0; i < 3; i++) {
		__set_payload_data(handle, 0x03);

		__set_payload_e_hi(handle); // E -> 1
		__send_payload(handle);

		__set_payload_e_lo(handle); // E -> 0
		__send_payload(handle);

		delay_ms(10);
	}

	//Set data interface to 4 bits
	__set_payload_data(handle, 0x02);

	__set_payload_e_hi(handle);
	__send_payload(handle);

	__set_payload_e_lo(handle);
	__send_payload(handle);

	//4 bits interface enabled. Now we can use high level functions like lcd_write_command, etc...

	//Function set
	__hd44780_write_instruction(handle, LCD_FUNCTION_SET | LCD_4_BITS | LCD_2_LINES | LCD_FONT_5_8);

	//Display off
	__hd44780_write_instruction(handle, LCD_ON_OFF | LCD_DISPLAY_OFF | LCD_CURSOR_OFF | LCD_CURSOR_NO_BLINK);

	//Display clear
	__hd44780_write_instruction(handle, LCD_CLEAR);

	//Entry mode
	__hd44780_write_instruction(handle, LCD_ENTRY_MODE | LCD_EM_CURSOR_INCREMENT);

	//Initialization done.

	//////////---------------------////////////////////
	hd44780_backlight(handle, BACKLIGHT_ON);
	__hd44780_write_instruction(handle, LCD_ON_OFF | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_CURSOR_BLINK);
}

void hd44780_backlight(hd44780_handle_t handle, enum backlight status) 
{
	handle->_backlight_status = status;
}

void hd44780_display_text(hd44780_handle_t handle, char* text)
{
	while(*(text)) {
		__hd44780_write_char(handle, *text);
		++text;
	}
}

void hd44780_set_options(hd44780_handle_t handle, uint8_t options)
{
	__hd44780_write_instruction(handle, LCD_ON_OFF | options);
}

void hd44780_set_position(hd44780_handle_t handle, uint8_t line_nr, uint8_t position)
{
	uint8_t data = 0;

	if (line_nr == LINE_1) {
		data = LINE_1;
	} else {
		data = LINE_2;
	}
	data += position;
	data |= (1 << D7);

	__hd44780_write_instruction(handle, data);
}

void hd44780_clear(hd44780_handle_t handle)
{
	__hd44780_write_instruction(handle, LCD_CLEAR);
}

void hd44780_home(hd44780_handle_t handle)
{
	__hd44780_write_instruction(handle, LCD_HOME);
}

//PIVATE FUNCTIONS IMPLEMENTATION
void __hd44780_write_instruction(hd44780_handle_t handle, uint8_t command)
{
	//Send first nibble
	__set_payload_data(handle, (command & 0xF0) >> 4);
	__set_payload_e_hi(handle);
	__send_payload(handle);
	__set_payload_e_lo(handle);
	__send_payload(handle);

	//Send second nibble
	__set_payload_data(handle, command & 0x0F);
	__set_payload_e_hi(handle);
	__send_payload(handle);
	__set_payload_e_lo(handle);
	__send_payload(handle);

	__clear_all(handle);
	__send_payload(handle);

		if (handle->busy_flag) {
		while (__is_busy());
	} else {
		delay_ms(10);
	}

}

void __hd44780_write_char(hd44780_handle_t handle, char c)
{
	__set_payload_rs_hi(handle);
	__hd44780_write_instruction(handle, c);
	__set_payload_rs_lo(handle);
}