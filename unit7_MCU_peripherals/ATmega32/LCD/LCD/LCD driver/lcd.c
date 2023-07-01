/*
 * lcd.c
 *
 * Created: 6/2/2023 10:53:08 AM
 *  Author: Hassan
 */ 

#include "lcd.h"

void LCD_kick()
{
	LCD_CTRL &= ~(1<<EN_switch); //no command during
	_delay_ms(50);
	LCD_CTRL |= (1<<EN_switch);//enable
}

void LCD_GOTO_XY(int line,int position)
{
	if (line == 1)
	{
		 if (position <16 && position>=0)
		 {
			  LCD_write_command(LCD_Begin_at_first_row + position);
		 }
		
	}
	else if(line == 2)
	{
		if (position <32 && position>=0)
		{
			LCD_write_command(LCD_Begin_at_second_row + position);
		}
	}
	
}
void LCD_isbusy()
{
	//Data_dir_LCD_PORT &= ~ (0xFF << data_shift); //inputl
	Data_dir_LCD_PORT= 0x00; //inputl
	LCD_CTRL |= (1<<RW_switch);//read mode
	LCD_CTRL &= ~(1<<RS_switch);
	LCD_kick();
	Data_dir_LCD_PORT =0xFF;
	LCD_CTRL &= ~(1<<RW_switch);
}
 
 void LCD_Clear_screen()
 {
	 LCD_write_command(LCD_clear_screen);
 }

void LCD_init()
{
	_delay_ms(20);
	LCD_isbusy();
	Data_dir_LCD_CTRL |= (1<<EN_switch) | (1<<RW_switch) | (1<<RS_switch);
	LCD_CTRL &= ~(1<<EN_switch) | (1<<RW_switch) | (1<<RS_switch);
	Data_dir_LCD_PORT = 0xFF; //output
	LCD_Clear_screen();
	#ifdef Eight_bit_mode 
		LCD_write_command(LCD_function_8bit_2line);
	#endif
	#ifdef four_bit_mode
		LCD_write_command(0x02);
		LCD_write_command(LCD_function_4bit_2line);
	#endif
	LCD_write_command(LCD_entry_mode);
	LCD_write_command(LCD_Begin_at_first_row);
	LCD_write_command(LCD_DISP_on_cursor_blink);
}

void LCD_write_command(unsigned char command)
{
	LCD_isbusy();
	
	#ifdef Eight_bit_mode
	
	LCD_PORT = command;
	LCD_CTRL &= ~(1<<RW_switch) | (1<<RS_switch);
	LCD_kick();
	#endif

	#ifdef four_bit_mode
		LCD_PORT = (LCD_PORT & 0x0F) |  (command & 0xF0) ;
		LCD_CTRL &= ~((1<<RW_switch) | (1<<RS_switch));
		_delay_ms(1);
		LCD_kick();
		LCD_PORT = (LCD_PORT & 0x0F) |  (command << 4 ) ;
		LCD_CTRL &= ~((1<<RW_switch) | (1<<RS_switch));
		_delay_ms(1);
		LCD_kick();
	#endif	
}

void LCD_write_char(unsigned char data)
{
	LCD_isbusy();
	#ifdef Eight_bit_mode
		LCD_CTRL |=  (1<<RS_switch);
		LCD_PORT = data;
		LCD_CTRL &= ~(1<<RW_switch) ;
		LCD_CTRL |= (1<<RS_switch);
		LCD_kick();
	#endif

	#ifdef four_bit_mode
		LCD_PORT = (LCD_PORT & 0x0F) |  (data & 0xF0) ;
		LCD_CTRL &= ~(1<<RW_switch) ;
		LCD_CTRL |= (1<<RS_switch);
		_delay_ms(1);
		LCD_kick();
		LCD_PORT = (LCD_PORT & 0x0F) |  (data << 4 ) ;
		LCD_CTRL &= ~(1<<RW_switch) ;
		LCD_CTRL |= (1<<RS_switch);
		_delay_ms(1);
		LCD_kick();
	#endif
}

void LCD_write_string(char* data)
{
	int count =0;
	
	while(*data > 0)
	{
		count++;
		LCD_write_char(*data++);
		if(count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		if (count ==32)
		{
			LCD_Clear_screen();
			LCD_GOTO_XY(1,0);
			count =0;
		}
	}
}