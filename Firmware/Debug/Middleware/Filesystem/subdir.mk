################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/Filesystem/Filesystem.c 

OBJS += \
./Middleware/Filesystem/Filesystem.o 

C_DEPS += \
./Middleware/Filesystem/Filesystem.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/Filesystem/%.o Middleware/Filesystem/%.su Middleware/Filesystem/%.cyclo: ../Middleware/Filesystem/%.c Middleware/Filesystem/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Driver" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Application" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Devices" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Middleware" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-Filesystem

clean-Middleware-2f-Filesystem:
	-$(RM) ./Middleware/Filesystem/Filesystem.cyclo ./Middleware/Filesystem/Filesystem.d ./Middleware/Filesystem/Filesystem.o ./Middleware/Filesystem/Filesystem.su

.PHONY: clean-Middleware-2f-Filesystem

