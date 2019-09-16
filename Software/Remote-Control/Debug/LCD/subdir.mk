################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD/LCDWIKI.c \
../LCD/simpleLCD.c 

CPP_SRCS += \
../LCD/Gui.cpp \
../LCD/mvm.cpp \
../LCD/settings.cpp 

OBJS += \
./LCD/Gui.o \
./LCD/LCDWIKI.o \
./LCD/mvm.o \
./LCD/settings.o \
./LCD/simpleLCD.o 

C_DEPS += \
./LCD/LCDWIKI.d \
./LCD/simpleLCD.d 

CPP_DEPS += \
./LCD/Gui.d \
./LCD/mvm.d \
./LCD/settings.d 


# Each subdirectory must supply rules for building sources it contributes
LCD/%.o: ../LCD/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/lvgl" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/App" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/System" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/LCD" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/Joystick" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/nRF905/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

LCD/%.o: ../LCD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/lvgl" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/App" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/System" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/Joystick" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/nRF905/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/LCD"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


