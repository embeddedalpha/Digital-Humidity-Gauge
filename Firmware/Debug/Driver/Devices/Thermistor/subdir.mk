################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Devices/Thermistor/Thermistor.c 

OBJS += \
./Driver/Devices/Thermistor/Thermistor.o 

C_DEPS += \
./Driver/Devices/Thermistor/Thermistor.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Devices/Thermistor/%.o Driver/Devices/Thermistor/%.su Driver/Devices/Thermistor/%.cyclo: ../Driver/Devices/Thermistor/%.c Driver/Devices/Thermistor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/DDC_Controller_V100/Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Devices-2f-Thermistor

clean-Driver-2f-Devices-2f-Thermistor:
	-$(RM) ./Driver/Devices/Thermistor/Thermistor.cyclo ./Driver/Devices/Thermistor/Thermistor.d ./Driver/Devices/Thermistor/Thermistor.o ./Driver/Devices/Thermistor/Thermistor.su

.PHONY: clean-Driver-2f-Devices-2f-Thermistor

