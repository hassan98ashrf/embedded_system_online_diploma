//startup.c
//lab3

#include  <stdint.h>

extern int main (void);
extern unsigned int  _E_TEXT;
extern unsigned int  _S_DATA;
extern unsigned int  _E_DATA;
extern unsigned int  _S_bss;
extern unsigned int  _E_bss;

void  reset_handler(){
	//copy .data  from flash to  ram
	unsigned int Data_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA;
	unsigned char* P_Src = (unsigned char*)&_E_TEXT;
	unsigned char* P_Dst = (unsigned char*)&_S_DATA;
	int i;

	for(i=0;i<Data_size;i++) {
		*P_Dst = *P_Src;
		P_Dst++;
		P_Src++;
	}

	// Init bss section in Ram with 0 
	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	P_Dst = (unsigned char*)&_S_bss;

	for(i=0;i<bss_size;i++) {
		*P_Dst = (unsigned char)0;
		P_Dst++;
	}

	main();
}


void default_handler (){
	reset_handler();
}

void NMI_handler ()  __attribute__((weak,alias("default_handler")));;
void H_fault_handler ()  __attribute__((weak,alias("default_handler")));;



static unsigned long  stack_top[256]; //  1024byte=256*4

void  (* const fun_to_vectors []) () __attribute__((section(".vectors"))) = 
{
    (void (*)()) ((unsigned long)stack_top + sizeof(stack_top)),
	 &reset_handler,
	 &NMI_handler,
	 &H_fault_handler
};



