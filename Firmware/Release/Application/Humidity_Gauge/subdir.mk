################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Humidity_Gauge/Humidity_Gauge.c 

OBJS += \
./Application/Humidity_Gauge/Humidity_Gauge.o 

C_DEPS += \
./Application/Humidity_Gauge/Humidity_Gauge.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Humidity_Gauge/%.o Application/Humidity_Gauge/%.su Application/Humidity_Gauge/%.cyclo: ../Application/Humidity_Gauge/%.c Application/Humidity_Gauge/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Driver" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices/BME280" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Application" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Humidity_Gauge

clean-Application-2f-Humidity_Gauge:
	-$(RM) ./Application/Humidity_Gauge/Humidity_Gauge.cyclo ./Application/Humidity_Gauge/Humidity_Gauge.d ./Application/Humidity_Gauge/Humidity_Gauge.o ./Application/Humidity_Gauge/Humidity_Gauge.su

.PHONY: clean-Application-2f-Humidity_Gauge

