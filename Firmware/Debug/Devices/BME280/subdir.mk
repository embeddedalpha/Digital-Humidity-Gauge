################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Devices/BME280/BME280.c 

OBJS += \
./Devices/BME280/BME280.o 

C_DEPS += \
./Devices/BME280/BME280.d 


# Each subdirectory must supply rules for building sources it contributes
Devices/BME280/%.o Devices/BME280/%.su Devices/BME280/%.cyclo: ../Devices/BME280/%.c Devices/BME280/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Driver" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices/BME280" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Devices-2f-BME280

clean-Devices-2f-BME280:
	-$(RM) ./Devices/BME280/BME280.cyclo ./Devices/BME280/BME280.d ./Devices/BME280/BME280.o ./Devices/BME280/BME280.su

.PHONY: clean-Devices-2f-BME280

