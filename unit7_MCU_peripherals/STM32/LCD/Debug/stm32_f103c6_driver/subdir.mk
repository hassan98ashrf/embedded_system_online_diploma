################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32_f103c6_driver/stm32_f103c6_driver_EXTI.c \
../stm32_f103c6_driver/stm32_f103c6_driver_GPIO.c 

OBJS += \
./stm32_f103c6_driver/stm32_f103c6_driver_EXTI.o \
./stm32_f103c6_driver/stm32_f103c6_driver_GPIO.o 

C_DEPS += \
./stm32_f103c6_driver/stm32_f103c6_driver_EXTI.d \
./stm32_f103c6_driver/stm32_f103c6_driver_GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_f103c6_driver/stm32_f103c6_driver_EXTI.o: ../stm32_f103c6_driver/stm32_f103c6_driver_EXTI.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"H:/kerlos diploma/embedded_system_online_diploma/unit7_MCU_peripherals/STM32/LCD/HAL/inc" -I"H:/kerlos diploma/embedded_system_online_diploma/unit7_MCU_peripherals/STM32/LCD/stm32_f103c6_driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_driver/stm32_f103c6_driver_EXTI.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_driver/stm32_f103c6_driver_GPIO.o: ../stm32_f103c6_driver/stm32_f103c6_driver_GPIO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"H:/kerlos diploma/embedded_system_online_diploma/unit7_MCU_peripherals/STM32/LCD/HAL/inc" -I"H:/kerlos diploma/embedded_system_online_diploma/unit7_MCU_peripherals/STM32/LCD/stm32_f103c6_driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_driver/stm32_f103c6_driver_GPIO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

