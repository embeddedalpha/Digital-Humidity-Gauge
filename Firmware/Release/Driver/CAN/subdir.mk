################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CAN/CAN.c 

OBJS += \
./Driver/CAN/CAN.o 

C_DEPS += \
./Driver/CAN/CAN.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CAN/%.o Driver/CAN/%.su Driver/CAN/%.cyclo: ../Driver/CAN/%.c Driver/CAN/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Driver" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices/BME280" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Application" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CAN

clean-Driver-2f-CAN:
	-$(RM) ./Driver/CAN/CAN.cyclo ./Driver/CAN/CAN.d ./Driver/CAN/CAN.o ./Driver/CAN/CAN.su

.PHONY: clean-Driver-2f-CAN

