################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Midware/Src/GUI.c 

OBJS += \
./Midware/Src/GUI.o 

C_DEPS += \
./Midware/Src/GUI.d 


# Each subdirectory must supply rules for building sources it contributes
Midware/Src/%.o Midware/Src/%.su: ../Midware/Src/%.c Midware/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F334x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/git_project/stm32F334_HAL_Control/F334Control_nucleo/Basic/Inc" -I"C:/git_project/stm32F334_HAL_Control/F334Control_nucleo/Midware/Inc" -I"C:/git_project/stm32F334_HAL_Control/F334Control_nucleo/Hardware/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Midware-2f-Src

clean-Midware-2f-Src:
	-$(RM) ./Midware/Src/GUI.d ./Midware/Src/GUI.o ./Midware/Src/GUI.su

.PHONY: clean-Midware-2f-Src

