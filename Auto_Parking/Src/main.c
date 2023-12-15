/**
 ******************************************************************************
 * @file           : main.c
 * @author         : NTI-Team 1
 *					 Team Members
 *					 - Eslam El-Sayed Refeat
 *					 - Mohamed Abd El-Naby Mohamed
 *					 - Rana Abd El-Salam Mohamed
 *					 - Salma Mohamed Hashim
 *					 - Shaimaa Mahmoud Samir
 *					 - Sherif Atef Sedek
 *					 - Youssef Ahmed Mohamed
 * @brief          : This Program for Auto parking application
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) NTI-Team 1.
 * All rights reserved.</center></h2>
 *
 ******************************************************************************
 */



/************************************ Includes ****************************************/
#include "RCC_interface.h"
#include "C1_US_SLCT.h"
#include "C2_VCLE_CNTRL.h"
#include "C3_VCLE_ALIGN.h"
#include "C4_SLOT_FIND.h"
#include "C5_PARKING/C5_PARKING.h"
#include "SYS_DIG_MNG.h"
#include "main.h"
#include "SW_Delay.h"

#define SCR_0		0
#define SCR_1		0
#define SCR_2		0
#define SCR_3		1
#define E_MODULE_INIT	1

u8 arr[4][100] ;
u8 i , j , k , l ;
u8 iAvg , jAvg, kAvg, lAvg ;
u32 iSum , jSum, kSum , lsum ;
ERROR_t get_distance(u16* frontDistance , u16* backDistance , u16* frontRightDistance , u16* backRightDistance);


int main(void)
{

	/*
	 * Local Variables
	 */



    /* Clock Initialization
     * System Clock : SYSCLK	 = 8 MHz
     * AHB    Clock : HCLK	     = 8 MHz
     * APB1   Clock : APB1CLK    = 8 MHz
     * APB2   Clock : APB2CLK    = 8 MHz
     */
	RCC_voidInitSysClocks();

	/*
	 * Component Initialization
	 *	C1_US_SLCT          : Used to Select One of Vehicle Ultrasonic
	 *  C2_VCLE_CNTRL		: Used to Control Vehicle Directions
	 *  C3_VCLE_ALIGN		: Used to Check Vehicle Alignment
	 *  C4_SLOT_FIND		: Used to Find Slot
	 *
	 *  SYS_DIG_Mng			: Used to log Errors
	 *
	 */
	APPC1_Init();
#if E_MODULE_INIT == 1
	C2VCONTROL_voidInit();
	C4SLTFIND_voidInit();
	DIGMngr_voidInit();
	C5VCLEPRK_voidInitParking();
	delay_init();
#endif


	for(;;)
	{
		US_ERROR_t LOC_eReturnState = US_INVALID_READING ;
#if SCR_0 == 1
		u16 data = 0 ;
		LOC_eReturnState = APPC1_SelectUltrasonc(FrontUS, &data);
		if(LOC_eReturnState != US_VALID_READING)
		{
			LOC_eReturnState++;
		}
		arr[FrontUS][i++] = data;
		LOC_eReturnState = APPC1_SelectUltrasonc(BackUS, &data);
		if(LOC_eReturnState != US_VALID_READING)
		{
			LOC_eReturnState++;
		}
		arr[BackUS][j++] = data;
		LOC_eReturnState= APPC1_SelectUltrasonc(FrontRightUS, &data);
		if(LOC_eReturnState != US_VALID_READING)
		{
			LOC_eReturnState++;
		}
		arr[FrontRightUS][k++] = data;
		LOC_eReturnState = APPC1_SelectUltrasonc(RearRightUS, &data);
		if(LOC_eReturnState != US_VALID_READING)
		{
			LOC_eReturnState++;
		}
		arr[RearRightUS][l++] = data;
		(void)LOC_eReturnState;
#endif
#if SCR_1 == 1
		u16 dataf = 0 , datab = 0 ,dataFR = 0 , dataBR = 0  ;
		LOC_eReturnState = get_distance(&dataf, &datab, &dataFR, &dataBR);
		arr[FrontUS][i++] = dataf;
		arr[BackUS][j++] = datab;
		arr[FrontRightUS][k++] = dataFR;
		arr[RearRightUS][l++] = dataBR;
#endif
#if SCR_2 == 1

		u16 dataf = 0 , datab = 0 ,dataFR = 0 , dataBR = 0  ;
		LOC_eReturnState = C4_StaticGetFourDistance(&dataf, &datab, &dataFR, &dataBR);
		arr[FrontUS][i++] = dataf;
		arr[BackUS][j++] = datab;
		arr[FrontRightUS][k++] = dataFR;
		arr[RearRightUS][l++] = dataBR;
#endif

#if SCR_3 == 1
		(void)LOC_eReturnState;
		if(C5VCLEPRK_voidStartParking3() == E_OK)
		{
			while(1);
		}
#endif

		if(i >= 100 || j >= 100 || k >= 100)
		{
			i = 0 ;
			k = 0 ;
			j = 0 ;
			l = 0 ;
			for(int c = 0 ; c < 100 ; c++)
			{
				iSum += arr[FrontUS][c] ;
				jSum += arr[BackUS][c] ;
				kSum += arr[FrontRightUS][c] ;
				lsum += arr[RearRightUS][c] ;
			}
			iAvg = iSum / 100 ;
			jAvg = jSum / 100 ;
			kAvg = kSum/100;
			lAvg = lsum / 100 ;
			iSum = 0 ;
			jSum = 0 ;
			kSum = 0 ;
			lsum = 0 ;
			if(C5VCLEPRK_voidStartParking3() == E_OK)
			{
				//while(1);
			}
			lsum = 0 ;
		}

	}
}

#if SCR_1 == 1
ERROR_t get_distance(u16* frontDistance , u16* backDistance , u16* frontRightDistance , u16* backRightDistance)
{
	u16 data = 0 ;
	US_ERROR_t LOC_eReturnState = US_INVALID_READING ;
	// Front
	LOC_eReturnState = APPC1_SelectUltrasonc(FrontUS, &data);
	if(LOC_eReturnState != US_VALID_READING)
	{
		return LOC_eReturnState ;
	}
	*frontDistance = (u8) data;
	data = 0 ;
	// Back
	LOC_eReturnState = APPC1_SelectUltrasonc(BackUS, &data);
	if(LOC_eReturnState != US_VALID_READING)
	{
		return LOC_eReturnState ;
	}
	*backDistance = (u8)data ;
	data = 0 ;

	// Front Right
	LOC_eReturnState= APPC1_SelectUltrasonc(FrontRightUS, &data);
	if(LOC_eReturnState != US_VALID_READING)
	{
		return LOC_eReturnState ;
	}
	*frontRightDistance = (u8)data ;
	data = 0 ;

	// Rear Right
	LOC_eReturnState = APPC1_SelectUltrasonc(RearRightUS, &data);
	if(LOC_eReturnState != US_VALID_READING)
	{
		return LOC_eReturnState ;
	}
	*backRightDistance = (u8)data ;
	data = 0 ;

	return LOC_eReturnState;
}
#endif
