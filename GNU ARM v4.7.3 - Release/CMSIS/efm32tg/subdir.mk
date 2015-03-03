################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/system_efm32tg.c 

S_UPPER_SRCS += \
C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/GCC/startup_efm32tg.S 

OBJS += \
./CMSIS/efm32tg/startup_efm32tg.o \
./CMSIS/efm32tg/system_efm32tg.o 

C_DEPS += \
./CMSIS/efm32tg/system_efm32tg.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/efm32tg/startup_efm32tg.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/GCC/startup_efm32tg.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -c -x assembler-with-cpp -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/EFM32TG_STK3300/examples/blink" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32TG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/EFM32TG_STK3300/config" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2\emdrv\gpiointerrupt\inc" '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/efm32tg/system_efm32tg.o: C:/SiliconLabs/SimplicityStudio/v2/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/system_efm32tg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' '-DNDEBUG=1' -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/EFM32TG_STK3300/examples/blink" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/CMSIS/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/emlib/inc" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/common/bsp" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/Device/SiliconLabs/EFM32TG/Include" -I"C:\SiliconLabs\SimplicityStudio\v2\developer\sdks\efm32\v2/kits/EFM32TG_STK3300/config" -O3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"CMSIS/efm32tg/system_efm32tg.d" -MT"CMSIS/efm32tg/system_efm32tg.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


