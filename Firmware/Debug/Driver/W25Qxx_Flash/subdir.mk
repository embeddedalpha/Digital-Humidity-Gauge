################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/W25Qxx_Flash/W25Qxx_Flash.c 

OBJS += \
./Driver/W25Qxx_Flash/W25Qxx_Flash.o 

C_DEPS += \
./Driver/W25Qxx_Flash/W25Qxx_Flash.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/W25Qxx_Flash/%.o Driver/W25Qxx_Flash/%.su Driver/W25Qxx_Flash/%.cyclo: ../Driver/W25Qxx_Flash/%.c Driver/W25Qxx_Flash/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Driver" -I"D:/STM32F407_Projects/Digital-Humidity-Gauge/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-W25Qxx_Flash

clean-Driver-2f-W25Qxx_Flash:
	-$(RM) ./Driver/W25Qxx_Flash/W25Qxx_Flash.cyclo ./Driver/W25Qxx_Flash/W25Qxx_Flash.d ./Driver/W25Qxx_Flash/W25Qxx_Flash.o ./Driver/W25Qxx_Flash/W25Qxx_Flash.su

.PHONY: clean-Driver-2f-W25Qxx_Flash

