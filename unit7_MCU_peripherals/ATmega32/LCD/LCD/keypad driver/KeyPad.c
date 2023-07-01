/*
 * KeyPad.c
 *
 * Created: 6/2/2023 12:16:12 PM
 *  Author: hassa
 */ 
#include "KeyPad.h"
int KeyPad_R[] = {R0 ,R1 ,R2 , R3};
int KeyPad_C[] = {C0 ,C1 ,C2 , C3};


void KeyPad_Init()
{
	Data_dir_KeyPad_PORT &= ~((1<<R0)| (1<<R1)| (1<<R2)| (1<<R3));
	Data_dir_KeyPad_PORT |=  ((1<<C0)| (1<<C1)| (1<<C2)| (1<<C3));
	KeyPad_PORT = 0xFF;
}

char KeyPad_Get_char()
{
	int i,j;
	for (i=0 ; i <4 ;i++)
	{
		KeyPad_PORT |=( (1<<KeyPad_C[0]) | (1<<KeyPad_C[1]) | (1<<KeyPad_C[2]) | (1<<KeyPad_C[3]) ) ;
		KeyPad_PORT &= ~ (1<<KeyPad_C[i]);
		for (j=0 ; j<4 ; j++)
		{
			if (!(KeyPad_PIN & (1<<KeyPad_R[j])))//multi pressing
			{
				while(!(KeyPad_PIN & (1<<KeyPad_R[j])));
				switch(i)
				{
					case (0):
						if(j==0) return '7';
						else if(j==1) return '4';
						else if(j==2) return '1';
						else if(j==3) return '!';	
						break;
					case (1):
						if(j==0) return '8';
						else if(j==1) return '5';
						else if(j==2) return '2';
						else if(j==3) return '0';
						break;
					case (2):
						if(j==0) return '9';
						else if(j==1) return '6';
						else if(j==2) return '3';
						else if(j==3) return '=';	
						break;
					case (3):
						if(j==0) return '/';
						else if(j==1) return '*';
						else if(j==2) return '-';
						else if(j==3) return '+';
						break;
				}
			}
		}
		
		
		
	}
	return 'N';
}