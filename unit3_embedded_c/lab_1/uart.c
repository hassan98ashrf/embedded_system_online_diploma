#include "uart.h"
#define UART0DR *((volatile unsigned int*const)((unsigned int *) 0x101f1000))

void send_string (unsigned char * tx_send){
	while(tx_send != '\0'){
		UART0DR = (unsigned int)(*tx_send);
		tx_send++;
	}
}