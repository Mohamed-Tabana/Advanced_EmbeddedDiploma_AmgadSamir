################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/DMA_prg.c \
../Src/GPIO_prg.c \
../Src/I2C_prg.c \
../Src/NVIC_prg.c \
../Src/RCC_prg.c \
../Src/RTC.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/DMA_prg.o \
./Src/GPIO_prg.o \
./Src/I2C_prg.o \
./Src/NVIC_prg.o \
./Src/RCC_prg.o \
./Src/RTC.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/DMA_prg.d \
./Src/GPIO_prg.d \
./Src/I2C_prg.d \
./Src/NVIC_prg.d \
./Src/RCC_prg.d \
./Src/RTC.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/DMA_prg.cyclo ./Src/DMA_prg.d ./Src/DMA_prg.o ./Src/DMA_prg.su ./Src/GPIO_prg.cyclo ./Src/GPIO_prg.d ./Src/GPIO_prg.o ./Src/GPIO_prg.su ./Src/I2C_prg.cyclo ./Src/I2C_prg.d ./Src/I2C_prg.o ./Src/I2C_prg.su ./Src/NVIC_prg.cyclo ./Src/NVIC_prg.d ./Src/NVIC_prg.o ./Src/NVIC_prg.su ./Src/RCC_prg.cyclo ./Src/RCC_prg.d ./Src/RCC_prg.o ./Src/RCC_prg.su ./Src/RTC.cyclo ./Src/RTC.d ./Src/RTC.o ./Src/RTC.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

