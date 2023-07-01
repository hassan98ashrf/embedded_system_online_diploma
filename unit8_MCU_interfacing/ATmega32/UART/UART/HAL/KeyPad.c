/*
 * KeyPad.c
 *
 * Created: 6/26/2023 10:16:03 AM
 *  Author: hassa
 */ 
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "inc/KeyPad.h"




//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========= GENERIC VARIABLES ==========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
int keypad_R [4]= {R0 , R1 , R2 , R3};	 //Array of rows numbers
int keypad_C [4]= {C0 , C1 , C2 , C3};	 //Array of the columns numbers


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by " HAL KEYPAD DRIVER " ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


/**================================================================
* @Fn		- KeyPad_Init
* @brief    - initialize the KEYPAD
* @retval   - none
*/
void KeyPad_Init(){
	KEYPAD_COLUMNS_OUTPUT  = (KEYPAD_COLUMNS_OUTPUT & ~COLUMNS_PINS) | COLUMNS_PINS;   //Make all columns output one

}

/**================================================================
* @Fn      - KeyPad_get_char
* @brief   - Get input from the KEYPAD
* @retval  - Character
*/

char KeyPad_get_char(){
	int i,j;
	//Switch zero between columns to get the char
	for (i = 0; i < 4; i++){
		KEYPAD_COLUMNS_OUTPUT = (KEYPAD_COLUMNS_OUTPUT & ~COLUMNS_PINS) | COLUMNS_PINS;		//Make all columns output one
		KEYPAD_COLUMNS_OUTPUT &= (1 << keypad_C[i]); 	//Make one columns output zero
		for(j = 0; j < 4 ; j++){		//Check if any row's input is zero
			if(!(KEYPAD_ROWS_INPUT & (1 << keypad_R[j]))){
				while(!(KEYPAD_ROWS_INPUT & (1 << keypad_R[j])));
				//Get the character according to row and columns
				switch (i){
					case(0):
					if( j == 0) return '7';
					else if (j == 1) return '4';
					else if (j == 2) return '1';
					else if (j == 3) return '!';
					break;
					case(1):
					if( j == 0) return '8';
					else if (j == 1) return '5';
					else if (j == 2) return '2';
					else if (j == 3) return '0';
					break;
					case(2):
					if( j == 0) return '9';
					else if (j == 1) return '6';
					else if (j == 2) return '3';
					else if (j == 3) return '=';
					break;
					case(3):
					if( j == 0) return '/';
					else if (j == 1) return '*';
					else if (j == 2) return '-';
					else if (j == 3) return '+';
					break;
				}
				
			}
		}
	}
	return '\0';
}

