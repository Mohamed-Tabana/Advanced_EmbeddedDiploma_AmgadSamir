################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/EXTI_cfg.c \
../Src/MCAL/EXTI_prg.c \
../Src/MCAL/GPIO_cfg.c \
../Src/MCAL/GPIO_prg.c \
../Src/MCAL/NVIC_prg.c \
../Src/MCAL/RCC_prg.c \
../Src/MCAL/SPI_cfg.c \
../Src/MCAL/SPI_prg.c \
../Src/MCAL/SysTick_prg.c 

OBJS += \
./Src/MCAL/EXTI_cfg.o \
./Src/MCAL/EXTI_prg.o \
./Src/MCAL/GPIO_cfg.o \
./Src/MCAL/GPIO_prg.o \
./Src/MCAL/NVIC_prg.o \
./Src/MCAL/RCC_prg.o \
./Src/MCAL/SPI_cfg.o \
./Src/MCAL/SPI_prg.o \
./Src/MCAL/SysTick_prg.o 

C_DEPS += \
./Src/MCAL/EXTI_cfg.d \
./Src/MCAL/EXTI_prg.d \
./Src/MCAL/GPIO_cfg.d \
./Src/MCAL/GPIO_prg.d \
./Src/MCAL/NVIC_prg.d \
./Src/MCAL/RCC_prg.d \
./Src/MCAL/SPI_cfg.d \
./Src/MCAL/SPI_prg.d \
./Src/MCAL/SysTick_prg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/%.o Src/MCAL/%.su Src/MCAL/%.cyclo: ../Src/MCAL/%.c Src/MCAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL

clean-Src-2f-MCAL:
	-$(RM) ./Src/MCAL/EXTI_cfg.cyclo ./Src/MCAL/EXTI_cfg.d ./Src/MCAL/EXTI_cfg.o ./Src/MCAL/EXTI_cfg.su ./Src/MCAL/EXTI_prg.cyclo ./Src/MCAL/EXTI_prg.d ./Src/MCAL/EXTI_prg.o ./Src/MCAL/EXTI_prg.su ./Src/MCAL/GPIO_cfg.cyclo ./Src/MCAL/GPIO_cfg.d ./Src/MCAL/GPIO_cfg.o ./Src/MCAL/GPIO_cfg.su ./Src/MCAL/GPIO_prg.cyclo ./Src/MCAL/GPIO_prg.d ./Src/MCAL/GPIO_prg.o ./Src/MCAL/GPIO_prg.su ./Src/MCAL/NVIC_prg.cyclo ./Src/MCAL/NVIC_prg.d ./Src/MCAL/NVIC_prg.o ./Src/MCAL/NVIC_prg.su ./Src/MCAL/RCC_prg.cyclo ./Src/MCAL/RCC_prg.d ./Src/MCAL/RCC_prg.o ./Src/MCAL/RCC_prg.su ./Src/MCAL/SPI_cfg.cyclo ./Src/MCAL/SPI_cfg.d ./Src/MCAL/SPI_cfg.o ./Src/MCAL/SPI_cfg.su ./Src/MCAL/SPI_prg.cyclo ./Src/MCAL/SPI_prg.d ./Src/MCAL/SPI_prg.o ./Src/MCAL/SPI_prg.su ./Src/MCAL/SysTick_prg.cyclo ./Src/MCAL/SysTick_prg.d ./Src/MCAL/SysTick_prg.o ./Src/MCAL/SysTick_prg.su

.PHONY: clean-Src-2f-MCAL

