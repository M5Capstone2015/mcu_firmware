################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include Drivers/subdir.mk
-include CMSIS/efm32tg/subdir.mk
-include BSP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: STK3300_pox_spi.axf

# Tool invocations
STK3300_pox_spi.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb  --specs=nano.specs -Xlinker --gc-sections -Xlinker -Map="STK3300_pox_spi.map" -T "STK3300_pox_spi.ld" -o STK3300_pox_spi.axf "./src/main.o" "./src/spi.o" "./src/usart.o" "./emlib/em_assert.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_int.o" "./emlib/em_system.o" "./emlib/em_usart.o" "./Drivers/gpiointerrupt.o" "./CMSIS/efm32tg/startup_efm32tg.o" "./CMSIS/efm32tg/system_efm32tg.o" "./BSP/bsp_bcc.o" "./BSP/bsp_stk.o" "./BSP/bsp_stk_leds.o" "./BSP/bsp_trace.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: STK3300_pox_spi.hex'
	arm-none-eabi-objcopy -O ihex "STK3300_pox_spi.axf" "STK3300_pox_spi.hex"
	@echo ' '

	@echo 'Building bin file: STK3300_pox_spi.bin'
	arm-none-eabi-objcopy -O binary "STK3300_pox_spi.axf" "STK3300_pox_spi.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "STK3300_pox_spi.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) STK3300_pox_spi.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
