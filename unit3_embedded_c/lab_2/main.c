
#include <stdint.h>
#define RCC_BASE 	    0x40021000
#define PORTA_BASE 	  	0x40010800
#define RCC_APB2ENR 	*(volatile uint32_t *)(RCC_BASE + 0x18)
#define GPIOA_CRH 		*(volatile uint32_t *)(PORTA_BASE + 0x04)        /*from bit 20 to 24 Mode pin13=2*/
#define GPIOA_ODR 		*(volatile uint32_t *)(PORTA_BASE + 0x0C)

#define RCC_IOPAEN 		(1<<2)
#define GPIOA13			(1UL<<13)

typedef union {
	volatile uint32_t all_fields;
	struct{
		volatile uint32_t reserved:13;
		volatile uint32_t Pin13:1;
	}Pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(PORTA_BASE + 0x0C) ;

int main(void)
{
	RCC_APB2ENR |= RCC_IOPAEN;
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;
	while(1){
		R_ODR->Pin.Pin13=0;
		int i;
		for(i =0; i< 1000;i++);          /*DELAY*/
		R_ODR->Pin.Pin13=1;
		for(i =0; i< 1000;i++);
	}
	
	return 0;
}
