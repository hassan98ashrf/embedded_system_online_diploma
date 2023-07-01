/*
 * lcd.h
 *
 * Created: 6/2/2023 10:52:53 AM
 *  Author: Hassan
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000UL

#include  <avr/io.h>
#include  <util/delay.h>



#define LCD_PORT PORTA
#define Data_dir_LCD_PORT DDRA
#define LCD_CTRL PORTB
#define Data_dir_LCD_CTRL DDRB

#define RS_switch 1
#define RW_switch 2
#define EN_switch 3
#define data_shift 4

#define Eight_bit_mode
//#define four_bit_mode

#define  LCD_function_8bit_2line	(0x38)
#define  LCD_function_4bit_2line	(0x28)
#define  LCD_move_DISP_right		(0x1C)
#define  LCD_move_DISP_left			(0x18)
#define  LCD_move_cursor_right		(0x14)
#define  LCD_move_cursor_left		(0x10)
#define  LCD_DISP_off				(0x08)
#define  LCD_DISP_on_cursor			(0x0E)
#define  LCD_DISP_on_cursor_blink	(0x0F)
#define  LCD_DISP_on_blink			(0x0D)
#define  LCD_DISP_on				(0x0C)
#define  LCD_entry_DEC				(0x04)
#define  LCD_entry_DEC_shift		(0x05)
#define  LCD_entry_INC				(0x06)
#define  LCD_entry_INC_shift		(0x07)
#define  LCD_Begin_at_first_row		(0x80)
#define  LCD_Begin_at_second_row	(0xC0)
#define  LCD_clear_screen			(0x01)
#define  LCD_entry_mode				(0x06)


void LCD_init (void);
void LCD_write_command (unsigned char command);
void LCD_write_char (unsigned char data);
void LCD_write_string ( char* data);
void LCD_isbusy (void);
void LCD_Clear_screen (void);









#endif /* LCD_H_ */