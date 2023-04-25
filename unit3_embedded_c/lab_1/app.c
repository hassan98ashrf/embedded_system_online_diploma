#include "uart.h"
unsigned char txt [100] = "Learn-In-Depth: Hassan A, Elsalakawy";

void main(void){
	send_string (txt);
}