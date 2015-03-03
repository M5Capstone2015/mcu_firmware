################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emdrv/gpiointerrupt/src/gpiointerrupt.c 

OBJS += \
./Drivers/gpiointerrupt.o 

C_DEPS += \
./Drivers/gpiointerrupt.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/gpiointerrupt.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/emdrv/gpiointerrupt/src/gpiointerrupt.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' '-DNDEBUG=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/EFM32TG_STK3300/examples/blink" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32TG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/EFM32TG_STK3300/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2\emdrv\gpiointerrupt\inc" -O3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"Drivers/gpiointerrupt.d" -MT"Drivers/gpiointerrupt.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


