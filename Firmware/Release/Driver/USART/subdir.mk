################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/USART/USART.c 

OBJS += \
./Driver/USART/USART.o 

C_DEPS += \
./Driver/USART/USART.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/USART/%.o Driver/USART/%.su Driver/USART/%.cyclo: ../Driver/USART/%.c Driver/USART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Driver" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices/BME280" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Application" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-USART

clean-Driver-2f-USART:
	-$(RM) ./Driver/USART/USART.cyclo ./Driver/USART/USART.d ./Driver/USART/USART.o ./Driver/USART/USART.su

.PHONY: clean-Driver-2f-USART

