################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Services/APP_Services.c \
../Src/Services/SPI_Services.c 

OBJS += \
./Src/Services/APP_Services.o \
./Src/Services/SPI_Services.o 

C_DEPS += \
./Src/Services/APP_Services.d \
./Src/Services/SPI_Services.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Services/%.o Src/Services/%.su Src/Services/%.cyclo: ../Src/Services/%.c Src/Services/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Services

clean-Src-2f-Services:
	-$(RM) ./Src/Services/APP_Services.cyclo ./Src/Services/APP_Services.d ./Src/Services/APP_Services.o ./Src/Services/APP_Services.su ./Src/Services/SPI_Services.cyclo ./Src/Services/SPI_Services.d ./Src/Services/SPI_Services.o ./Src/Services/SPI_Services.su

.PHONY: clean-Src-2f-Services

