################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/MCAL/RCC/RCC.c 

OBJS += \
./Inc/MCAL/RCC/RCC.o 

C_DEPS += \
./Inc/MCAL/RCC/RCC.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/MCAL/RCC/RCC.o: ../Inc/MCAL/RCC/RCC.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -c -I../Inc -I"C:/Users/hassa/Downloads/auto/Inc/HAL/DC" -I"C:/Users/hassa/Downloads/auto/Inc/HAL/US" -I"C:/Users/hassa/Downloads/auto/Inc/LIB" -I"C:/Users/hassa/Downloads/auto/Inc/MCAL/GPIO" -I"C:/Users/hassa/Downloads/auto/Inc/MCAL/ICU" -I"C:/Users/hassa/Downloads/auto/Inc/MCAL/NVIC" -I"C:/Users/hassa/Downloads/auto/Inc/MCAL/PWM" -I"C:/Users/hassa/Downloads/auto/Inc/MCAL/RCC" -I"C:/Users/hassa/Downloads/auto/Inc/MCAL/STK" -I"C:/Users/hassa/Downloads/auto/Inc/MCAL/USART" -I"C:/Users/hassa/Downloads/auto/Inc/SERVICE/ALIG_CAR" -I"C:/Users/hassa/Downloads/auto/Inc/SERVICE/CAR_PARK" -I"C:/Users/hassa/Downloads/auto/Inc/SERVICE/CTRL_CAR" -I"C:/Users/hassa/Downloads/auto/Inc/SERVICE/FIND_PARKING" -I"C:/Users/hassa/Downloads/auto/Inc/SERVICE/SELECT_US" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MCAL/RCC/RCC.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

