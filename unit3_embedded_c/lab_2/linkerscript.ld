ENTRY(reset)

MEMORY
 {
     flash (RX)  : ORIGIN = 0x08000000, LENGTH = 128K
     sram  (RWX) : ORIGIN = 0X20000000, LENGTH = 20K
 }

 SECTIONS
 {
     .text :{
         *(.vectors*)
         *(.text*) 
         *(.rodata*)
     }> flash

     .data :{
         *(.data*)
     }> sram 

     .bss :{
         *(.bss)
     }> sram
 }