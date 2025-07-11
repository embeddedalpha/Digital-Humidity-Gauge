################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/SPI/SPI.c 

OBJS += \
./Driver/SPI/SPI.o 

C_DEPS += \
./Driver/SPI/SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/SPI/%.o Driver/SPI/%.su Driver/SPI/%.cyclo: ../Driver/SPI/%.c Driver/SPI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Driver" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices/BME280" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Application" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-SPI

clean-Driver-2f-SPI:
	-$(RM) ./Driver/SPI/SPI.cyclo ./Driver/SPI/SPI.d ./Driver/SPI/SPI.o ./Driver/SPI/SPI.su

.PHONY: clean-Driver-2f-SPI

