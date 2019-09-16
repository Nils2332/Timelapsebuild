################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_misc/lv_anim.c \
../lvgl/lv_misc/lv_area.c \
../lvgl/lv_misc/lv_circ.c \
../lvgl/lv_misc/lv_color.c \
../lvgl/lv_misc/lv_font.c \
../lvgl/lv_misc/lv_fs.c \
../lvgl/lv_misc/lv_gc.c \
../lvgl/lv_misc/lv_ll.c \
../lvgl/lv_misc/lv_log.c \
../lvgl/lv_misc/lv_math.c \
../lvgl/lv_misc/lv_mem.c \
../lvgl/lv_misc/lv_task.c \
../lvgl/lv_misc/lv_templ.c \
../lvgl/lv_misc/lv_txt.c \
../lvgl/lv_misc/lv_ufs.c 

OBJS += \
./lvgl/lv_misc/lv_anim.o \
./lvgl/lv_misc/lv_area.o \
./lvgl/lv_misc/lv_circ.o \
./lvgl/lv_misc/lv_color.o \
./lvgl/lv_misc/lv_font.o \
./lvgl/lv_misc/lv_fs.o \
./lvgl/lv_misc/lv_gc.o \
./lvgl/lv_misc/lv_ll.o \
./lvgl/lv_misc/lv_log.o \
./lvgl/lv_misc/lv_math.o \
./lvgl/lv_misc/lv_mem.o \
./lvgl/lv_misc/lv_task.o \
./lvgl/lv_misc/lv_templ.o \
./lvgl/lv_misc/lv_txt.o \
./lvgl/lv_misc/lv_ufs.o 

C_DEPS += \
./lvgl/lv_misc/lv_anim.d \
./lvgl/lv_misc/lv_area.d \
./lvgl/lv_misc/lv_circ.d \
./lvgl/lv_misc/lv_color.d \
./lvgl/lv_misc/lv_font.d \
./lvgl/lv_misc/lv_fs.d \
./lvgl/lv_misc/lv_gc.d \
./lvgl/lv_misc/lv_ll.d \
./lvgl/lv_misc/lv_log.d \
./lvgl/lv_misc/lv_math.d \
./lvgl/lv_misc/lv_mem.d \
./lvgl/lv_misc/lv_task.d \
./lvgl/lv_misc/lv_templ.d \
./lvgl/lv_misc/lv_txt.d \
./lvgl/lv_misc/lv_ufs.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_misc/%.o: ../lvgl/lv_misc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/lvgl" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/App" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/System" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/Joystick" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/nRF905/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/LCD"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


