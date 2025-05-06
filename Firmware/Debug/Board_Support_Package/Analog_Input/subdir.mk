################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Support_Package/Analog_Input/Analog_Input.c 

OBJS += \
./Board_Support_Package/Analog_Input/Analog_Input.o 

C_DEPS += \
./Board_Support_Package/Analog_Input/Analog_Input.d 


# Each subdirectory must supply rules for building sources it contributes
Board_Support_Package/Analog_Input/%.o Board_Support_Package/Analog_Input/%.su Board_Support_Package/Analog_Input/%.cyclo: ../Board_Support_Package/Analog_Input/%.c Board_Support_Package/Analog_Input/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/DDC_Controller_V100/Devices" -I"D:/STM32F407_Projects/DDC_Controller_V100/Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Board_Support_Package-2f-Analog_Input

clean-Board_Support_Package-2f-Analog_Input:
	-$(RM) ./Board_Support_Package/Analog_Input/Analog_Input.cyclo ./Board_Support_Package/Analog_Input/Analog_Input.d ./Board_Support_Package/Analog_Input/Analog_Input.o ./Board_Support_Package/Analog_Input/Analog_Input.su

.PHONY: clean-Board_Support_Package-2f-Analog_Input

