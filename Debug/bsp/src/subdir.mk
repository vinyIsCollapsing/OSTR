################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/src/bsp.c 

OBJS += \
./bsp/src/bsp.o 

C_DEPS += \
./bsp/src/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/src/%.o bsp/src/%.su bsp/src/%.cyclo: ../bsp/src/%.c bsp/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -c -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/app/inc" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/bsp/src" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/bsp/inc" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/cmsis/core" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/cmsis/device/inc" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/app/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsp-2f-src

clean-bsp-2f-src:
	-$(RM) ./bsp/src/bsp.cyclo ./bsp/src/bsp.d ./bsp/src/bsp.o ./bsp/src/bsp.su

.PHONY: clean-bsp-2f-src

