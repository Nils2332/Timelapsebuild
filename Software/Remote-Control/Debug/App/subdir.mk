################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../App/App.cpp 

OBJS += \
./App/App.o 

CPP_DEPS += \
./App/App.d 


# Each subdirectory must supply rules for building sources it contributes
App/%.o: ../App/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Inc" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/CMSIS/Include" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/lvgl" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/App" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/System" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/LCD" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/Joystick" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/nRF905/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


