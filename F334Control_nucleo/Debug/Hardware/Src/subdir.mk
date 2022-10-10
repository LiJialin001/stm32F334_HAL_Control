################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/Src/lcd7735.c \
../Hardware/Src/ssd1309.c \
../Hardware/Src/ssd1309_fonts.c 

OBJS += \
./Hardware/Src/lcd7735.o \
./Hardware/Src/ssd1309.o \
./Hardware/Src/ssd1309_fonts.o 

C_DEPS += \
./Hardware/Src/lcd7735.d \
./Hardware/Src/ssd1309.d \
./Hardware/Src/ssd1309_fonts.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/Src/%.o Hardware/Src/%.su: ../Hardware/Src/%.c Hardware/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F334x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/git_project/stm32F334_HAL_Control/F334Control_nucleo/Basic/Inc" -I"C:/git_project/stm32F334_HAL_Control/F334Control_nucleo/Midware/Inc" -I"C:/git_project/stm32F334_HAL_Control/F334Control_nucleo/Hardware/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Hardware-2f-Src

clean-Hardware-2f-Src:
	-$(RM) ./Hardware/Src/lcd7735.d ./Hardware/Src/lcd7735.o ./Hardware/Src/lcd7735.su ./Hardware/Src/ssd1309.d ./Hardware/Src/ssd1309.o ./Hardware/Src/ssd1309.su ./Hardware/Src/ssd1309_fonts.d ./Hardware/Src/ssd1309_fonts.o ./Hardware/Src/ssd1309_fonts.su

.PHONY: clean-Hardware-2f-Src

