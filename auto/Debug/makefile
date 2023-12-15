################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Inc/SERVICE/SELECT_US/subdir.mk
-include Inc/SERVICE/FIND_PARKING/subdir.mk
-include Inc/SERVICE/CTRL_CAR/subdir.mk
-include Inc/SERVICE/CAR_PARK/subdir.mk
-include Inc/SERVICE/ALIG_CAR/subdir.mk
-include Inc/MCAL/USART/subdir.mk
-include Inc/MCAL/STK/subdir.mk
-include Inc/MCAL/RCC/subdir.mk
-include Inc/MCAL/PWM/subdir.mk
-include Inc/MCAL/NVIC/subdir.mk
-include Inc/MCAL/ICU/subdir.mk
-include Inc/MCAL/GPIO/subdir.mk
-include Inc/LIB/subdir.mk
-include Inc/HAL/US/subdir.mk
-include Inc/HAL/DC/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
autoParking.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
autoParking.list \

OBJCOPY_BIN += \
autoParking.bin \


# All Target
all: autoParking.elf secondary-outputs

# Tool invocations
autoParking.elf: $(OBJS) $(USER_OBJS) C:\Users\hassa\Downloads\auto\STM32F303RETX_FLASH.ld
	arm-none-eabi-gcc -o "autoParking.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\hassa\Downloads\auto\STM32F303RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="autoParking.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

autoParking.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "autoParking.list"
	@echo 'Finished building: $@'
	@echo ' '

autoParking.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "autoParking.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
