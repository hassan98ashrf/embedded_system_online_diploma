CC			 =arm-none-eabi-
CFLAGS 		 =-mcpu=cortex-m4 -mthumb -gdwarf-2 -g
INCS		 =-I .
LIBS		 =
SRC			 =$(wildcard *.c)
OBJ			 =$(SRC:.c=.o)
ASM    		 =$(wildcard *.s)
ASMOBJ 		 =$(ASM:.s=.o)
LINKER 		 =$(wildcard *.ld)
Project_Name = unit3_lab3_cortex_m4


all: $(Project_Name).bin
	@echo "====mission completed====="


%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) -c $< -o $@


$(Project_Name).elf : $(OBJ) $(ASMOBJ)
	$(CC)ld.exe -T $(LINKER) $(OBJ) $(ASMOBJ) $(LIBS) -Map=Map_File.map -o $@ -Map=Map_file.map
	cp $(Project_Name).elf $(Project_Name).axf

$(Project_Name).bin : $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin

clean:
	rm *.bin *.elf