################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_draw/lv_draw.c \
../lvgl/lv_draw/lv_draw_arc.c \
../lvgl/lv_draw/lv_draw_img.c \
../lvgl/lv_draw/lv_draw_label.c \
../lvgl/lv_draw/lv_draw_line.c \
../lvgl/lv_draw/lv_draw_rbasic.c \
../lvgl/lv_draw/lv_draw_rect.c \
../lvgl/lv_draw/lv_draw_triangle.c \
../lvgl/lv_draw/lv_draw_vbasic.c 

OBJS += \
./lvgl/lv_draw/lv_draw.o \
./lvgl/lv_draw/lv_draw_arc.o \
./lvgl/lv_draw/lv_draw_img.o \
./lvgl/lv_draw/lv_draw_label.o \
./lvgl/lv_draw/lv_draw_line.o \
./lvgl/lv_draw/lv_draw_rbasic.o \
./lvgl/lv_draw/lv_draw_rect.o \
./lvgl/lv_draw/lv_draw_triangle.o \
./lvgl/lv_draw/lv_draw_vbasic.o 

C_DEPS += \
./lvgl/lv_draw/lv_draw.d \
./lvgl/lv_draw/lv_draw_arc.d \
./lvgl/lv_draw/lv_draw_img.d \
./lvgl/lv_draw/lv_draw_label.d \
./lvgl/lv_draw/lv_draw_line.d \
./lvgl/lv_draw/lv_draw_rbasic.d \
./lvgl/lv_draw/lv_draw_rect.d \
./lvgl/lv_draw/lv_draw_triangle.d \
./lvgl/lv_draw/lv_draw_vbasic.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_draw/%.o: ../lvgl/lv_draw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/lvgl" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/App" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/System" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/Joystick" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/nRF905/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/LCD"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


