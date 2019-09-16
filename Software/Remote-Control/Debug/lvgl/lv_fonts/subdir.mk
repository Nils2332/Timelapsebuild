################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_fonts/lv_font_builtin.c \
../lvgl/lv_fonts/lv_font_dejavu_10.c \
../lvgl/lv_fonts/lv_font_dejavu_10_cyrillic.c \
../lvgl/lv_fonts/lv_font_dejavu_10_latin_sup.c \
../lvgl/lv_fonts/lv_font_dejavu_20.c \
../lvgl/lv_fonts/lv_font_dejavu_20_cyrillic.c \
../lvgl/lv_fonts/lv_font_dejavu_20_latin_sup.c \
../lvgl/lv_fonts/lv_font_dejavu_30.c \
../lvgl/lv_fonts/lv_font_dejavu_30_cyrillic.c \
../lvgl/lv_fonts/lv_font_dejavu_30_latin_sup.c \
../lvgl/lv_fonts/lv_font_dejavu_40.c \
../lvgl/lv_fonts/lv_font_dejavu_40_cyrillic.c \
../lvgl/lv_fonts/lv_font_dejavu_40_latin_sup.c \
../lvgl/lv_fonts/lv_font_monospace_8.c \
../lvgl/lv_fonts/lv_font_symbol_10.c \
../lvgl/lv_fonts/lv_font_symbol_20.c \
../lvgl/lv_fonts/lv_font_symbol_30.c \
../lvgl/lv_fonts/lv_font_symbol_40.c 

OBJS += \
./lvgl/lv_fonts/lv_font_builtin.o \
./lvgl/lv_fonts/lv_font_dejavu_10.o \
./lvgl/lv_fonts/lv_font_dejavu_10_cyrillic.o \
./lvgl/lv_fonts/lv_font_dejavu_10_latin_sup.o \
./lvgl/lv_fonts/lv_font_dejavu_20.o \
./lvgl/lv_fonts/lv_font_dejavu_20_cyrillic.o \
./lvgl/lv_fonts/lv_font_dejavu_20_latin_sup.o \
./lvgl/lv_fonts/lv_font_dejavu_30.o \
./lvgl/lv_fonts/lv_font_dejavu_30_cyrillic.o \
./lvgl/lv_fonts/lv_font_dejavu_30_latin_sup.o \
./lvgl/lv_fonts/lv_font_dejavu_40.o \
./lvgl/lv_fonts/lv_font_dejavu_40_cyrillic.o \
./lvgl/lv_fonts/lv_font_dejavu_40_latin_sup.o \
./lvgl/lv_fonts/lv_font_monospace_8.o \
./lvgl/lv_fonts/lv_font_symbol_10.o \
./lvgl/lv_fonts/lv_font_symbol_20.o \
./lvgl/lv_fonts/lv_font_symbol_30.o \
./lvgl/lv_fonts/lv_font_symbol_40.o 

C_DEPS += \
./lvgl/lv_fonts/lv_font_builtin.d \
./lvgl/lv_fonts/lv_font_dejavu_10.d \
./lvgl/lv_fonts/lv_font_dejavu_10_cyrillic.d \
./lvgl/lv_fonts/lv_font_dejavu_10_latin_sup.d \
./lvgl/lv_fonts/lv_font_dejavu_20.d \
./lvgl/lv_fonts/lv_font_dejavu_20_cyrillic.d \
./lvgl/lv_fonts/lv_font_dejavu_20_latin_sup.d \
./lvgl/lv_fonts/lv_font_dejavu_30.d \
./lvgl/lv_fonts/lv_font_dejavu_30_cyrillic.d \
./lvgl/lv_fonts/lv_font_dejavu_30_latin_sup.d \
./lvgl/lv_fonts/lv_font_dejavu_40.d \
./lvgl/lv_fonts/lv_font_dejavu_40_cyrillic.d \
./lvgl/lv_fonts/lv_font_dejavu_40_latin_sup.d \
./lvgl/lv_fonts/lv_font_monospace_8.d \
./lvgl/lv_fonts/lv_font_symbol_10.d \
./lvgl/lv_fonts/lv_font_symbol_20.d \
./lvgl/lv_fonts/lv_font_symbol_30.d \
./lvgl/lv_fonts/lv_font_symbol_40.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_fonts/%.o: ../lvgl/lv_fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/CMSIS/Include" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/lvgl" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/App" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/System" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/Joystick" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/Drivers/nRF905/Inc" -I"C:/Users/Nils/Documents/Projects/TimelapsBuild V2/Software/Remote-Control/LCD"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


