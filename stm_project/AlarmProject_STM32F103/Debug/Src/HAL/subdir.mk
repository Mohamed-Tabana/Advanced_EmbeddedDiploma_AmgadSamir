################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/LCD.c \
../Src/HAL/LCD_cfg.c 

OBJS += \
./Src/HAL/LCD.o \
./Src/HAL/LCD_cfg.o 

C_DEPS += \
./Src/HAL/LCD.d \
./Src/HAL/LCD_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/%.o Src/HAL/%.su Src/HAL/%.cyclo: ../Src/HAL/%.c Src/HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL

clean-Src-2f-HAL:
	-$(RM) ./Src/HAL/LCD.cyclo ./Src/HAL/LCD.d ./Src/HAL/LCD.o ./Src/HAL/LCD.su ./Src/HAL/LCD_cfg.cyclo ./Src/HAL/LCD_cfg.d ./Src/HAL/LCD_cfg.o ./Src/HAL/LCD_cfg.su

.PHONY: clean-Src-2f-HAL

