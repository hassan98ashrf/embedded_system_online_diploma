################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32_f103c6_driver/stm32_f103c6_driver_EXTI.c \
../stm32_f103c6_driver/stm32_f103c6_driver_GPIO.c \
../stm32_f103c6_driver/stm32_f103c6_driver_I2C.c \
../stm32_f103c6_driver/stm32_f103c6_driver_RCC.c \
../stm32_f103c6_driver/stm32_f103c6_driver_SPI.c \
../stm32_f103c6_driver/stm32_f103c6_driver_USART.c 

OBJS += \
./stm32_f103c6_driver/stm32_f103c6_driver_EXTI.o \
./stm32_f103c6_driver/stm32_f103c6_driver_GPIO.o \
./stm32_f103c6_driver/stm32_f103c6_driver_I2C.o \
./stm32_f103c6_driver/stm32_f103c6_driver_RCC.o \
./stm32_f103c6_driver/stm32_f103c6_driver_SPI.o \
./stm32_f103c6_driver/stm32_f103c6_driver_USART.o 

C_DEPS += \
./stm32_f103c6_driver/stm32_f103c6_driver_EXTI.d \
./stm32_f103c6_driver/stm32_f103c6_driver_GPIO.d \
./stm32_f103c6_driver/stm32_f103c6_driver_I2C.d \
./stm32_f103c6_driver/stm32_f103c6_driver_RCC.d \
./stm32_f103c6_driver/stm32_f103c6_driver_SPI.d \
./stm32_f103c6_driver/stm32_f103c6_driver_USART.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_f103c6_driver/stm32_f103c6_driver_EXTI.o: ../stm32_f103c6_driver/stm32_f103c6_driver_EXTI.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"H:/kerlos diploma/embedded_system_online_diploma/unit8_MCU_interfacing/STM32/I2C/stm32_f103c6_driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_driver/stm32_f103c6_driver_EXTI.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_driver/stm32_f103c6_driver_GPIO.o: ../stm32_f103c6_driver/stm32_f103c6_driver_GPIO.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"H:/kerlos diploma/embedded_system_online_diploma/unit8_MCU_interfacing/STM32/I2C/stm32_f103c6_driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_driver/stm32_f103c6_driver_GPIO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_driver/stm32_f103c6_driver_I2C.o: ../stm32_f103c6_driver/stm32_f103c6_driver_I2C.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"H:/kerlos diploma/embedded_system_online_diploma/unit8_MCU_interfacing/STM32/I2C/stm32_f103c6_driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_driver/stm32_f103c6_driver_I2C.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_driver/stm32_f103c6_driver_RCC.o: ../stm32_f103c6_driver/stm32_f103c6_driver_RCC.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"H:/kerlos diploma/embedded_system_online_diploma/unit8_MCU_interfacing/STM32/I2C/stm32_f103c6_driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_driver/stm32_f103c6_driver_RCC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_driver/stm32_f103c6_driver_SPI.o: ../stm32_f103c6_driver/stm32_f103c6_driver_SPI.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"H:/kerlos diploma/embedded_system_online_diploma/unit8_MCU_interfacing/STM32/I2C/stm32_f103c6_driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_driver/stm32_f103c6_driver_SPI.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_driver/stm32_f103c6_driver_USART.o: ../stm32_f103c6_driver/stm32_f103c6_driver_USART.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"H:/kerlos diploma/embedded_system_online_diploma/unit8_MCU_interfacing/STM32/I2C/stm32_f103c6_driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_driver/stm32_f103c6_driver_USART.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

