################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Devices/Seven_Segement_Display/Seven_Segment_Display.c 

OBJS += \
./Driver/Devices/Seven_Segement_Display/Seven_Segment_Display.o 

C_DEPS += \
./Driver/Devices/Seven_Segement_Display/Seven_Segment_Display.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Devices/Seven_Segement_Display/%.o Driver/Devices/Seven_Segement_Display/%.su Driver/Devices/Seven_Segement_Display/%.cyclo: ../Driver/Devices/Seven_Segement_Display/%.c Driver/Devices/Seven_Segement_Display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/DDC_Controller_V100/Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Devices-2f-Seven_Segement_Display

clean-Driver-2f-Devices-2f-Seven_Segement_Display:
	-$(RM) ./Driver/Devices/Seven_Segement_Display/Seven_Segment_Display.cyclo ./Driver/Devices/Seven_Segement_Display/Seven_Segment_Display.d ./Driver/Devices/Seven_Segement_Display/Seven_Segment_Display.o ./Driver/Devices/Seven_Segement_Display/Seven_Segment_Display.su

.PHONY: clean-Driver-2f-Devices-2f-Seven_Segement_Display

