

MEMORY {
	Flash(RX) : ORIGIN = 0x00000000, LENGTH = 512M
	SRAM(RWX) : ORIGIN = 0x20000000, LENGTH = 512M
}
SECTIONS {
	.text : {
		*(.vectors*)
		. = ALIGN(4) ;
		*(.text*)
		. = ALIGN(4) ;
		*(.rodata*)
		. = ALIGN(4) ;
		_E_TEXT = .;
	}> Flash 
	
	.data : {
		_S_DATA = .;
		*(.data*)
		. = ALIGN(4) ; 
		_E_DATA = .;
	}> SRAM AT> Flash
	
	.bss : {
		_S_bss = .;
		*(.bss*)
		. = ALIGN(4) ;
		_E_bss = .;
	}> SRAM
}