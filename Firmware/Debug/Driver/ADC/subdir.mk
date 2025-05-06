################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/ADC/ADC.c 

OBJS += \
./Driver/ADC/ADC.o 

C_DEPS += \
./Driver/ADC/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/ADC/%.o Driver/ADC/%.su Driver/ADC/%.cyclo: ../Driver/ADC/%.c Driver/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/DDC_Controller_V100/Devices" -I"D:/STM32F407_Projects/DDC_Controller_V100/Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-ADC

clean-Driver-2f-ADC:
	-$(RM) ./Driver/ADC/ADC.cyclo ./Driver/ADC/ADC.d ./Driver/ADC/ADC.o ./Driver/ADC/ADC.su

.PHONY: clean-Driver-2f-ADC

