################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_core/lv_group.c \
../lvgl/lv_core/lv_indev.c \
../lvgl/lv_core/lv_lang.c \
../lvgl/lv_core/lv_obj.c \
../lvgl/lv_core/lv_refr.c \
../lvgl/lv_core/lv_style.c \
../lvgl/lv_core/lv_vdb.c 

OBJS += \
./lvgl/lv_core/lv_group.o \
./lvgl/lv_core/lv_indev.o \
./lvgl/lv_core/lv_lang.o \
./lvgl/lv_core/lv_obj.o \
./lvgl/lv_core/lv_refr.o \
./lvgl/lv_core/lv_style.o \
./lvgl/lv_core/lv_vdb.o 

C_DEPS += \
./lvgl/lv_core/lv_group.d \
./lvgl/lv_core/lv_indev.d \
./lvgl/lv_core/lv_lang.d \
./lvgl/lv_core/lv_obj.d \
./lvgl/lv_core/lv_refr.d \
./lvgl/lv_core/lv_style.d \
./lvgl/lv_core/lv_vdb.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_core/%.o: ../lvgl/lv_core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Inc" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/CMSIS/Include" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/lvgl" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/App" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/System" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/Joystick" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/nRF905/Inc" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/LCD"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


