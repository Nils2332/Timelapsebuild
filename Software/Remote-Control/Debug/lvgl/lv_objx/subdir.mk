################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_objx/lv_arc.c \
../lvgl/lv_objx/lv_bar.c \
../lvgl/lv_objx/lv_btn.c \
../lvgl/lv_objx/lv_btnm.c \
../lvgl/lv_objx/lv_calendar.c \
../lvgl/lv_objx/lv_canvas.c \
../lvgl/lv_objx/lv_cb.c \
../lvgl/lv_objx/lv_chart.c \
../lvgl/lv_objx/lv_cont.c \
../lvgl/lv_objx/lv_ddlist.c \
../lvgl/lv_objx/lv_gauge.c \
../lvgl/lv_objx/lv_img.c \
../lvgl/lv_objx/lv_imgbtn.c \
../lvgl/lv_objx/lv_kb.c \
../lvgl/lv_objx/lv_label.c \
../lvgl/lv_objx/lv_led.c \
../lvgl/lv_objx/lv_line.c \
../lvgl/lv_objx/lv_list.c \
../lvgl/lv_objx/lv_lmeter.c \
../lvgl/lv_objx/lv_mbox.c \
../lvgl/lv_objx/lv_objx_templ.c \
../lvgl/lv_objx/lv_page.c \
../lvgl/lv_objx/lv_preload.c \
../lvgl/lv_objx/lv_roller.c \
../lvgl/lv_objx/lv_slider.c \
../lvgl/lv_objx/lv_spinbox.c \
../lvgl/lv_objx/lv_sw.c \
../lvgl/lv_objx/lv_ta.c \
../lvgl/lv_objx/lv_table.c \
../lvgl/lv_objx/lv_tabview.c \
../lvgl/lv_objx/lv_tileview.c \
../lvgl/lv_objx/lv_win.c 

OBJS += \
./lvgl/lv_objx/lv_arc.o \
./lvgl/lv_objx/lv_bar.o \
./lvgl/lv_objx/lv_btn.o \
./lvgl/lv_objx/lv_btnm.o \
./lvgl/lv_objx/lv_calendar.o \
./lvgl/lv_objx/lv_canvas.o \
./lvgl/lv_objx/lv_cb.o \
./lvgl/lv_objx/lv_chart.o \
./lvgl/lv_objx/lv_cont.o \
./lvgl/lv_objx/lv_ddlist.o \
./lvgl/lv_objx/lv_gauge.o \
./lvgl/lv_objx/lv_img.o \
./lvgl/lv_objx/lv_imgbtn.o \
./lvgl/lv_objx/lv_kb.o \
./lvgl/lv_objx/lv_label.o \
./lvgl/lv_objx/lv_led.o \
./lvgl/lv_objx/lv_line.o \
./lvgl/lv_objx/lv_list.o \
./lvgl/lv_objx/lv_lmeter.o \
./lvgl/lv_objx/lv_mbox.o \
./lvgl/lv_objx/lv_objx_templ.o \
./lvgl/lv_objx/lv_page.o \
./lvgl/lv_objx/lv_preload.o \
./lvgl/lv_objx/lv_roller.o \
./lvgl/lv_objx/lv_slider.o \
./lvgl/lv_objx/lv_spinbox.o \
./lvgl/lv_objx/lv_sw.o \
./lvgl/lv_objx/lv_ta.o \
./lvgl/lv_objx/lv_table.o \
./lvgl/lv_objx/lv_tabview.o \
./lvgl/lv_objx/lv_tileview.o \
./lvgl/lv_objx/lv_win.o 

C_DEPS += \
./lvgl/lv_objx/lv_arc.d \
./lvgl/lv_objx/lv_bar.d \
./lvgl/lv_objx/lv_btn.d \
./lvgl/lv_objx/lv_btnm.d \
./lvgl/lv_objx/lv_calendar.d \
./lvgl/lv_objx/lv_canvas.d \
./lvgl/lv_objx/lv_cb.d \
./lvgl/lv_objx/lv_chart.d \
./lvgl/lv_objx/lv_cont.d \
./lvgl/lv_objx/lv_ddlist.d \
./lvgl/lv_objx/lv_gauge.d \
./lvgl/lv_objx/lv_img.d \
./lvgl/lv_objx/lv_imgbtn.d \
./lvgl/lv_objx/lv_kb.d \
./lvgl/lv_objx/lv_label.d \
./lvgl/lv_objx/lv_led.d \
./lvgl/lv_objx/lv_line.d \
./lvgl/lv_objx/lv_list.d \
./lvgl/lv_objx/lv_lmeter.d \
./lvgl/lv_objx/lv_mbox.d \
./lvgl/lv_objx/lv_objx_templ.d \
./lvgl/lv_objx/lv_page.d \
./lvgl/lv_objx/lv_preload.d \
./lvgl/lv_objx/lv_roller.d \
./lvgl/lv_objx/lv_slider.d \
./lvgl/lv_objx/lv_spinbox.d \
./lvgl/lv_objx/lv_sw.d \
./lvgl/lv_objx/lv_ta.d \
./lvgl/lv_objx/lv_table.d \
./lvgl/lv_objx/lv_tabview.d \
./lvgl/lv_objx/lv_tileview.d \
./lvgl/lv_objx/lv_win.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_objx/%.o: ../lvgl/lv_objx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/lvgl" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/App" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/System" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/Joystick" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/nRF905/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/LCD"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


