################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/MCAL/RCC/RCC_program.c 

OBJS += \
./Inc/MCAL/RCC/RCC_program.o 

C_DEPS += \
./Inc/MCAL/RCC/RCC_program.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/MCAL/RCC/RCC_program.o: ../Inc/MCAL/RCC/RCC_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/APP" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MCAL/RCC/RCC_program.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

