################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middleware/Filesystem/subdir.mk
-include Driver/USART/subdir.mk
-include Driver/Timer/subdir.mk
-include Driver/SPI/subdir.mk
-include Driver/RTC/subdir.mk
-include Driver/Logs/subdir.mk
-include Driver/I2C/subdir.mk
-include Driver/GPIO/subdir.mk
-include Driver/DMA/subdir.mk
-include Driver/Console/subdir.mk
-include Driver/CAN/subdir.mk
-include Devices/W25Qxx_Flash/subdir.mk
-include Devices/GC9A01/subdir.mk
-include Devices/BME280/subdir.mk
-include Application/Humidity_Gauge/subdir.mk
-include Application/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Digital-Humidity-Gauge
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Digital-Humidity-Gauge.elf \

MAP_FILES += \
Digital-Humidity-Gauge.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Digital-Humidity-Gauge.list \


# All Target
all: main-build

# Main-build Target
main-build: Digital-Humidity-Gauge.elf secondary-outputs

# Tool invocations
Digital-Humidity-Gauge.elf Digital-Humidity-Gauge.map: $(OBJS) $(USER_OBJS) D:\STM32F407_Projects\Digital-Humidity-Gauge\STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Digital-Humidity-Gauge.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\STM32F407_Projects\Digital-Humidity-Gauge\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Digital-Humidity-Gauge.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Digital-Humidity-Gauge.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Digital-Humidity-Gauge.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Digital-Humidity-Gauge.elf Digital-Humidity-Gauge.list Digital-Humidity-Gauge.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
