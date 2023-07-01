################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/RCC_PRG.c 

OBJS += \
./Src/MCAL/RCC_PRG.o 

C_DEPS += \
./Src/MCAL/RCC_PRG.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/%.o Src/MCAL/%.su Src/MCAL/%.cyclo: ../Src/MCAL/%.c Src/MCAL/subdir.mk
	$(error unable to generate command line)

clean: clean-Src-2f-MCAL

clean-Src-2f-MCAL:
	-$(RM) ./Src/MCAL/RCC_PRG.cyclo ./Src/MCAL/RCC_PRG.d ./Src/MCAL/RCC_PRG.o ./Src/MCAL/RCC_PRG.su

.PHONY: clean-Src-2f-MCAL

