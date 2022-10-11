################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Basic/Src/i2c.c \
../Basic/Src/spi.c \
../Basic/Src/sys.c 

OBJS += \
./Basic/Src/i2c.o \
./Basic/Src/spi.o \
./Basic/Src/sys.o 

C_DEPS += \
./Basic/Src/i2c.d \
./Basic/Src/spi.d \
./Basic/Src/sys.d 


# Each subdirectory must supply rules for building sources it contributes
Basic/Src/%.o Basic/Src/%.su: ../Basic/Src/%.c Basic/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F334x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/git_project/stm32F334_HAL_Control/F334Control_nucleo/Basic/Inc" -I"C:/git_project/stm32F334_HAL_Control/F334Control_nucleo/Midware/Inc" -I"C:/git_project/stm32F334_HAL_Control/F334Control_nucleo/Hardware/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Basic-2f-Src

clean-Basic-2f-Src:
	-$(RM) ./Basic/Src/i2c.d ./Basic/Src/i2c.o ./Basic/Src/i2c.su ./Basic/Src/spi.d ./Basic/Src/spi.o ./Basic/Src/spi.su ./Basic/Src/sys.d ./Basic/Src/sys.o ./Basic/Src/sys.su

.PHONY: clean-Basic-2f-Src

