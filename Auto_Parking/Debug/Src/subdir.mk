################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/SYS_DIG_Mng" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C4_SLOT_FIND" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/APP" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL/DCMOTOR" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL/US" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/GPIO" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/ICU" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/NVIC" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/PWM" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/RCC" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C1_US_SLCT" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C2_VCLE_CNTRL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C3_VCLE_ALIGN" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/SYS_DIG_Mng" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C4_SLOT_FIND" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/APP" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL/DCMOTOR" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL/US" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/GPIO" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/ICU" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/NVIC" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/PWM" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/RCC" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C1_US_SLCT" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C2_VCLE_CNTRL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C3_VCLE_ALIGN" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/SYS_DIG_Mng" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C4_SLOT_FIND" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/APP" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL/DCMOTOR" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/HAL/US" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/LIB" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/GPIO" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/ICU" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/NVIC" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/PWM" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/MCAL/RCC" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C1_US_SLCT" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C2_VCLE_CNTRL" -I"C:/Users/hassa/Downloads/Auto_Parking/Inc/SERVICES/C3_VCLE_ALIGN" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

