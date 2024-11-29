################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/src/bsp.c \
../bsp/src/delay.c 

OBJS += \
./bsp/src/bsp.o \
./bsp/src/delay.o 

C_DEPS += \
./bsp/src/bsp.d \
./bsp/src/delay.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/src/%.o bsp/src/%.su bsp/src/%.cyclo: ../bsp/src/%.c bsp/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -c -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/app/inc" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/TraceRecorder/config" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/TraceRecorder/include" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/TraceRecorder/streamports/Jlink_RTT/config" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/TraceRecorder/streamports/Jlink_RTT/include" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/FreeRTOS/include" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/FreeRTOS/portable/GCC/ARM_CM0" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/bsp/inc" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/cmsis/core" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/cmsis/device/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsp-2f-src

clean-bsp-2f-src:
	-$(RM) ./bsp/src/bsp.cyclo ./bsp/src/bsp.d ./bsp/src/bsp.o ./bsp/src/bsp.su ./bsp/src/delay.cyclo ./bsp/src/delay.d ./bsp/src/delay.o ./bsp/src/delay.su

.PHONY: clean-bsp-2f-src

