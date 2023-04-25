
CC = arm-none-eabi-
CFLAGS = -g -mcpu=arm926ej-s
LIBS=
INCS= -I .
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
AS= $(wildcard *.s)
OBJAS= $(AS:.s=.o)
project_name = learn-in-depth

all:$(project_name).bin
	@echo "missio done"

startup.o : startup.s
	$(CC)as.exe $(CFLAGS)  $< -o $@
	
%.o : %.c
	$(CC)gcc.exe $(CFLAGS) -c $(INCS) $< -o $@
	
$(project_name).elf : $(OBJ) $(OBJAS)
	$(CC)ld.exe -T linkerscript.ld $(OBJ) $(OBJAS) -o $@
	
$(project_name).bin : $(project_name).elf
	$(CC)objcopy.exe -O binary $<  $@
	
clean_all:
	rm *.o *.elf *.bin

clean:
	rm  *.elf *.bin
	
