################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_porting/lv_port_disp_templ.c \
../lvgl/lv_porting/lv_port_fs_templ.c \
../lvgl/lv_porting/lv_port_indev_templ.c 

OBJS += \
./lvgl/lv_porting/lv_port_disp_templ.o \
./lvgl/lv_porting/lv_port_fs_templ.o \
./lvgl/lv_porting/lv_port_indev_templ.o 

C_DEPS += \
./lvgl/lv_porting/lv_port_disp_templ.d \
./lvgl/lv_porting/lv_port_fs_templ.d \
./lvgl/lv_porting/lv_port_indev_templ.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_porting/%.o: ../lvgl/lv_porting/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Inc" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/CMSIS/Include" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/lvgl" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/App" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/System" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/Joystick" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/Drivers/nRF905/Inc" -I"C:/Users/Nils/STMWorkbench/workspace/Timelapsebuild_2.1/LCD"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


