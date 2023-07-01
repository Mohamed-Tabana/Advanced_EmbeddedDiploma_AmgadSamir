################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f103c8tx.s 

OBJS += \
./Startup/startup_stm32f103c8tx.o 

S_DEPS += \
./Startup/startup_stm32f103c8tx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	$(error unable to generate command line)

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f103c8tx.d ./Startup/startup_stm32f103c8tx.o

.PHONY: clean-Startup

