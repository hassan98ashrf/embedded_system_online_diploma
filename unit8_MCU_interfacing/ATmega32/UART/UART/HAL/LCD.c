/*
 * LCD.c
 *
 * Created: 6/26/2023 10:27:41 AM
 *  Author: hassa
 */ 


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "inc/LCD.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by " HAL LCD DRIVER " ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


/**================================================================
* @Fn			- LCD_BF_check
* @brief		- Check if the LCD is busy or not (busy flag)
* @retval		- none
*/
/*
void LCD_BF_check(void){
	//CONFIG_DATA_CTRL(OUTPUT,INPUT);
	LCD_CTRL = (LCD_CTRL & LCD_WRITE_INSTRUCTION );
	LCD_CTRL = ((LCD_CTRL & ~(LCD_READ_INSTRUCTION)) | LCD_READ_INSTRUCTION);
	LCD_ENABLE;
	while((LCD_DATA >> BF_PIN) & 1);
}
*/

	
/**================================================================
* @Fn			- LCD_write_number
* @brief		- Write a real number on the LCD
* @param[in]	- Number needed to be displayed
* @retval		- None
*/													//Common functions between two modes
void LCD_write_number(int num){
	char str[16];
	sprintf(str,"%d",num);	//Convert the number into an array
	LCD_WRITE_STRING(str);	//Pass the array to LCD_WRITE_STRING function to be displayed
}


/**================================================================
* @Fn			- LCD_write_real_num
* @brief		- Write a float number to the LCD
* @param[in]	- Number needed to be displayed
* @retval		- None
*/
void LCD_write_real_num(double num){
	char str[16];
	char *Sign = (num < 0) ? "-" : "";	//Get the sign of the number
	float Val = (num < 0) ? -num : num ;  	//Make the number positive for calculations

	int Int1 = Val;		//Take the integer part of the number
	float Frac = Val - Int1;	//Get the fraction
	int Int2 = Frac * 10000;	//Make the fraction as integer

	sprintf(str ,"%c%d%c%.04d",Sign,Int1,'.',Int2);		//Convert the previous number into an array
	LCD_WRITE_STRING(str);		//Pass the array to LCD_WRITE_STRING function to be displayed
}
														
//===================================================================================================================================
#ifdef EIGHT_BIT_MODE


/**================================================================
* @Fn			- LCD_Init
* @brief		- initialize the LCD
* @retval		- none
*/
void LCD_INIT(void){

	//CONFIG_DATA_CTRL(OUTPUT,OUTPUT); todo
	LCD_WRITE_COMMAND(LCD_8BITS_2LINES_5X10);
	LCD_WRITE_COMMAND(LCD_DISP_ON);
	LCD_WRITE_COMMAND(LCD_Clear_Display);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}



/**================================================================
* @Fn			- LCD_write_command
* @brief		- Write a command in the  LCD
* @param[in]	- Command
*/
void LCD_write_command(unsigned char command){
	//CONFIG_DATA_CTRL(OUTPUT,OUTPUT);  todo
	LCD_CTRL = (LCD_CTRL & LCD_WRITE_INSTRUCTION);

//			  (				MASK	      ) | command
	LCD_DATA = (LCD_DATA & LCD_INPUT_PINS ) | command;
	_delay_ms(1);
	LCD_ENABLE;		//In header file

}


/**================================================================
* @Fn		 - LCD_write_char
* @brief	 - Write a character on the LCD
* @param[in] - Character
*/
void LCD_write_char(unsigned char character){
	static unsigned char COUNT_CHAR = 0 ;	//used for counting the characters displayed
	//CONFIG_DATA_CTRL(OUTPUT,OUTPUT);	todo
	if(character){

//			   (			MASK	     ) | character
	LCD_DATA = (LCD_DATA & LCD_INPUT_PINS) | character;

//			   (	      MASK			   ) | character
	LCD_CTRL = ((LCD_CTRL & ~LCD_WRITE_DATA) | LCD_WRITE_DATA);
	_delay_ms(1);
	LCD_ENABLE;
	COUNT_CHAR++;
}

//Check if the cursor at the end of the LCD row
	if (COUNT_CHAR == 16){	//if it at the edge of the first row
		GOTO_XY(0,1);		//Go to the second row
	}
	else if (COUNT_CHAR == 32){	//if it at the edge of the second row
		COUNT_CHAR = 0;
		LCD_WRITE_COMMAND(LCD_Clear_Display);	//Clear display
		GOTO_XY(0,0);	//Go to the first row
	}
}



/**================================================================
* @Fn			- LCD_write_string
* @brief		- Write a string to the LCD
* @param[in]	- String needed to be displayed
*/
void LCD_write_string(char* string){
	unsigned char i = 0 , COUNT_STRING = 1 ;//COUNT_STRING used for counting the characters displayed
	//CONFIG_DATA_CTRL(OUTPUT,OUTPUT);	todo
	while(string[i]){
//				   (	      MASK			   ) | Configurations
		LCD_CTRL = ((LCD_CTRL & ~LCD_WRITE_DATA) | LCD_WRITE_DATA);
//				   (	      MASK			   ) | string[i]
		LCD_DATA = (LCD_DATA & LCD_INPUT_PINS) | string[i];
		LCD_ENABLE;

		//Check if the cursor at the end of the LCD row
		if (COUNT_STRING == 15){	//if it at the edge of the first row
		GOTO_XY(0,1);				//Go to the second row
	}
	else if (COUNT_STRING == 30){	//if it at the edge of the second row
		COUNT_STRING = 0;
		LCD_WRITE_COMMAND(LCD_Clear_Display);	//Clear display
		GOTO_XY(0,0);	//Go to the first row
	}
		i++;
		COUNT_STRING++;
	}
}




#endif


		/**************************************/


#ifdef FOUR_BIT_MODE
/**================================================================
* @Fn			- LCD_Init
* @brief		- initialize the LCD
* @retval		- none
*/
void LCD_Init(){
	_delay_ms(20);
	//CONFIG_DATA_CTRL(OUTPUT,OUTPUT);
	LCD_CTRL &= ~(1 << EN);
	LCD_WRITE_COMMAND(LCD_Return_Home);
	LCD_WRITE_COMMAND(LCD_4BITS_2LINES_5X8);
	LCD_WRITE_COMMAND(LCD_DISP_ON);
	LCD_WRITE_COMMAND(LCD_Clear_Display);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
	
}


/**================================================================
* @Fn			- LCD_write_command
* @brief		- Write a command in the  LCD
* @param[in]	- Command
*/
void LCD_write_command(unsigned char command){
	//CONFIG_DATA_CTRL(OUTPUT,OUTPUT);
	LCD_CTRL = (LCD_CTRL & LCD_WRITE_INSTRUCTION);
	LCD_DATA = ((LCD_DATA & LCD_INPUT_PINS) | ((command & 0xF0) >> MOST_BIT_PIN));
	LCD_ENABLE;
	LCD_CTRL = (LCD_CTRL & LCD_WRITE_INSTRUCTION);
	LCD_DATA = ((LCD_DATA & LCD_INPUT_PINS) | ((command & 0x0F) << LEAST_BIT_PIN));
	LCD_ENABLE;
}


/**================================================================
* @Fn		 - LCD_write_char
* @brief	 - Write a character on the LCD
* @param[in] - Character
*/
void LCD_write_char(unsigned char character){
	static char COUNT_CHAR = 0 ;
	//CONFIG_DATA_CTRL(OUTPUT,OUTPUT);
	
	if(character){	
	LCD_CTRL = ((LCD_CTRL & ~LCD_WRITE_DATA) | LCD_WRITE_DATA);
	LCD_DATA = ((LCD_DATA & LCD_INPUT_PINS) | ((character & 0xF0) >> MOST_BIT_PIN));
	LCD_ENABLE;
	LCD_CTRL = ((LCD_CTRL & ~LCD_WRITE_DATA) | LCD_WRITE_DATA);
	LCD_DATA = ((LCD_DATA & LCD_INPUT_PINS) | ((character & 0x0F) << LEAST_BIT_PIN));
	LCD_ENABLE;
	COUNT_CHAR++;
	
}
	if (COUNT_CHAR == 16){
		GOTO_XY(0,1);
	}
	else if (COUNT_CHAR == 32){
		COUNT_CHAR = 0;
		LCD_write_command(LCD_Clear_Display);
		GOTO_XY(0,0);
	}
}


/**================================================================
* @Fn			- LCD_write_string
* @brief		- Write a string to the LCD
* @param[in]	- String needed to be displayed
*/
void LCD_write_string(char* string){
	unsigned char i = 0 , COUNT_STRING = 1 ;
	//CONFIG_DATA_CTRL(OUTPUT,OUTPUT);
	while(string[i]){
	LCD_CTRL = ((LCD_CTRL & ~LCD_WRITE_DATA) | LCD_WRITE_DATA);
	LCD_DATA = ((LCD_DATA & LCD_INPUT_PINS) | ((string[i] & 0xF0) >> MOST_BIT_PIN));
	LCD_ENABLE;
	LCD_CTRL = ((LCD_CTRL & ~LCD_WRITE_DATA) | LCD_WRITE_DATA);
	LCD_DATA = ((LCD_DATA & LCD_INPUT_PINS) | ((string[i] & 0x0F) << LEAST_BIT_PIN));
	LCD_ENABLE;
    COUNT_STRING++;
	if (COUNT_STRING == 16){
		GOTO_XY(0,1);
	}
	else if (COUNT_STRING == 32){
		COUNT_STRING = 0;
		LCD_write_command(LCD_Clear_Display);
		GOTO_XY(0,0);
	}
	i++;
	}
}
#endif




/**================================================================
* @Fn			- GOTO_XY
* @brief		- Moves the cursor in position (x,y)
* @param[in]	- position x in LCD
* @param[in]	- position y in LCD
* @retval		- None
*/
void GOTO_XY(unsigned char x ,unsigned char y){
	//CONFIG_DATA_CTRL(OUTPUT,OUTPUT); todo
	LCD_write_command(BAISX+x+BAISY*y);		//BAISX = 128 , BAISY = 64  from data sheet

}
