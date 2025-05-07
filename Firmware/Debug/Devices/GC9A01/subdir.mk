################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Devices/GC9A01/GC9A01.c 

OBJS += \
./Devices/GC9A01/GC9A01.o 

C_DEPS += \
./Devices/GC9A01/GC9A01.d 


# Each subdirectory must supply rules for building sources it contributes
Devices/GC9A01/%.o Devices/GC9A01/%.su Devices/GC9A01/%.cyclo: ../Devices/GC9A01/%.c Devices/GC9A01/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Driver" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Application" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Middleware" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Devices-2f-GC9A01

clean-Devices-2f-GC9A01:
	-$(RM) ./Devices/GC9A01/GC9A01.cyclo ./Devices/GC9A01/GC9A01.d ./Devices/GC9A01/GC9A01.o ./Devices/GC9A01/GC9A01.su

.PHONY: clean-Devices-2f-GC9A01

