################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/SERVICES/C5_PARKING/C5_PARKING.c 

OBJS += \
./Inc/SERVICES/C5_PARKING/C5_PARKING.o 

C_DEPS += \
./Inc/SERVICES/C5_PARKING/C5_PARKING.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/SERVICES/C5_PARKING/C5_PARKING.o: ../Inc/SERVICES/C5_PARKING/C5_PARKING.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/APP" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/SERVICES/C5_PARKING/C5_PARKING.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

