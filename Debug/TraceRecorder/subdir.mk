################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TraceRecorder/trcAssert.c \
../TraceRecorder/trcCounter.c \
../TraceRecorder/trcDependency.c \
../TraceRecorder/trcDiagnostics.c \
../TraceRecorder/trcEntryTable.c \
../TraceRecorder/trcError.c \
../TraceRecorder/trcEvent.c \
../TraceRecorder/trcEventBuffer.c \
../TraceRecorder/trcExtension.c \
../TraceRecorder/trcHardwarePort.c \
../TraceRecorder/trcHeap.c \
../TraceRecorder/trcISR.c \
../TraceRecorder/trcInternalEventBuffer.c \
../TraceRecorder/trcInterval.c \
../TraceRecorder/trcKernelPort.c \
../TraceRecorder/trcMultiCoreEventBuffer.c \
../TraceRecorder/trcObject.c \
../TraceRecorder/trcPrint.c \
../TraceRecorder/trcRunnable.c \
../TraceRecorder/trcSnapshotRecorder.c \
../TraceRecorder/trcStackMonitor.c \
../TraceRecorder/trcStateMachine.c \
../TraceRecorder/trcStaticBuffer.c \
../TraceRecorder/trcStreamingRecorder.c \
../TraceRecorder/trcString.c \
../TraceRecorder/trcTask.c \
../TraceRecorder/trcTimestamp.c 

OBJS += \
./TraceRecorder/trcAssert.o \
./TraceRecorder/trcCounter.o \
./TraceRecorder/trcDependency.o \
./TraceRecorder/trcDiagnostics.o \
./TraceRecorder/trcEntryTable.o \
./TraceRecorder/trcError.o \
./TraceRecorder/trcEvent.o \
./TraceRecorder/trcEventBuffer.o \
./TraceRecorder/trcExtension.o \
./TraceRecorder/trcHardwarePort.o \
./TraceRecorder/trcHeap.o \
./TraceRecorder/trcISR.o \
./TraceRecorder/trcInternalEventBuffer.o \
./TraceRecorder/trcInterval.o \
./TraceRecorder/trcKernelPort.o \
./TraceRecorder/trcMultiCoreEventBuffer.o \
./TraceRecorder/trcObject.o \
./TraceRecorder/trcPrint.o \
./TraceRecorder/trcRunnable.o \
./TraceRecorder/trcSnapshotRecorder.o \
./TraceRecorder/trcStackMonitor.o \
./TraceRecorder/trcStateMachine.o \
./TraceRecorder/trcStaticBuffer.o \
./TraceRecorder/trcStreamingRecorder.o \
./TraceRecorder/trcString.o \
./TraceRecorder/trcTask.o \
./TraceRecorder/trcTimestamp.o 

C_DEPS += \
./TraceRecorder/trcAssert.d \
./TraceRecorder/trcCounter.d \
./TraceRecorder/trcDependency.d \
./TraceRecorder/trcDiagnostics.d \
./TraceRecorder/trcEntryTable.d \
./TraceRecorder/trcError.d \
./TraceRecorder/trcEvent.d \
./TraceRecorder/trcEventBuffer.d \
./TraceRecorder/trcExtension.d \
./TraceRecorder/trcHardwarePort.d \
./TraceRecorder/trcHeap.d \
./TraceRecorder/trcISR.d \
./TraceRecorder/trcInternalEventBuffer.d \
./TraceRecorder/trcInterval.d \
./TraceRecorder/trcKernelPort.d \
./TraceRecorder/trcMultiCoreEventBuffer.d \
./TraceRecorder/trcObject.d \
./TraceRecorder/trcPrint.d \
./TraceRecorder/trcRunnable.d \
./TraceRecorder/trcSnapshotRecorder.d \
./TraceRecorder/trcStackMonitor.d \
./TraceRecorder/trcStateMachine.d \
./TraceRecorder/trcStaticBuffer.d \
./TraceRecorder/trcStreamingRecorder.d \
./TraceRecorder/trcString.d \
./TraceRecorder/trcTask.d \
./TraceRecorder/trcTimestamp.d 


# Each subdirectory must supply rules for building sources it contributes
TraceRecorder/%.o TraceRecorder/%.su TraceRecorder/%.cyclo: ../TraceRecorder/%.c TraceRecorder/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -c -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/app/inc" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/TraceRecorder/config" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/TraceRecorder/include" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/TraceRecorder/streamports/Jlink_RTT/config" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/TraceRecorder/streamports/Jlink_RTT/include" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/FreeRTOS/include" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/FreeRTOS/portable/GCC/ARM_CM0" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/bsp/inc" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/cmsis/core" -I"C:/Users/vinic/STM32CubeIDE/workspace_1.15.0/blink3/cmsis/device/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-TraceRecorder

clean-TraceRecorder:
	-$(RM) ./TraceRecorder/trcAssert.cyclo ./TraceRecorder/trcAssert.d ./TraceRecorder/trcAssert.o ./TraceRecorder/trcAssert.su ./TraceRecorder/trcCounter.cyclo ./TraceRecorder/trcCounter.d ./TraceRecorder/trcCounter.o ./TraceRecorder/trcCounter.su ./TraceRecorder/trcDependency.cyclo ./TraceRecorder/trcDependency.d ./TraceRecorder/trcDependency.o ./TraceRecorder/trcDependency.su ./TraceRecorder/trcDiagnostics.cyclo ./TraceRecorder/trcDiagnostics.d ./TraceRecorder/trcDiagnostics.o ./TraceRecorder/trcDiagnostics.su ./TraceRecorder/trcEntryTable.cyclo ./TraceRecorder/trcEntryTable.d ./TraceRecorder/trcEntryTable.o ./TraceRecorder/trcEntryTable.su ./TraceRecorder/trcError.cyclo ./TraceRecorder/trcError.d ./TraceRecorder/trcError.o ./TraceRecorder/trcError.su ./TraceRecorder/trcEvent.cyclo ./TraceRecorder/trcEvent.d ./TraceRecorder/trcEvent.o ./TraceRecorder/trcEvent.su ./TraceRecorder/trcEventBuffer.cyclo ./TraceRecorder/trcEventBuffer.d ./TraceRecorder/trcEventBuffer.o ./TraceRecorder/trcEventBuffer.su ./TraceRecorder/trcExtension.cyclo ./TraceRecorder/trcExtension.d ./TraceRecorder/trcExtension.o ./TraceRecorder/trcExtension.su ./TraceRecorder/trcHardwarePort.cyclo ./TraceRecorder/trcHardwarePort.d ./TraceRecorder/trcHardwarePort.o ./TraceRecorder/trcHardwarePort.su ./TraceRecorder/trcHeap.cyclo ./TraceRecorder/trcHeap.d ./TraceRecorder/trcHeap.o ./TraceRecorder/trcHeap.su ./TraceRecorder/trcISR.cyclo ./TraceRecorder/trcISR.d ./TraceRecorder/trcISR.o ./TraceRecorder/trcISR.su ./TraceRecorder/trcInternalEventBuffer.cyclo ./TraceRecorder/trcInternalEventBuffer.d ./TraceRecorder/trcInternalEventBuffer.o ./TraceRecorder/trcInternalEventBuffer.su ./TraceRecorder/trcInterval.cyclo ./TraceRecorder/trcInterval.d ./TraceRecorder/trcInterval.o ./TraceRecorder/trcInterval.su ./TraceRecorder/trcKernelPort.cyclo ./TraceRecorder/trcKernelPort.d ./TraceRecorder/trcKernelPort.o ./TraceRecorder/trcKernelPort.su ./TraceRecorder/trcMultiCoreEventBuffer.cyclo ./TraceRecorder/trcMultiCoreEventBuffer.d ./TraceRecorder/trcMultiCoreEventBuffer.o ./TraceRecorder/trcMultiCoreEventBuffer.su ./TraceRecorder/trcObject.cyclo ./TraceRecorder/trcObject.d ./TraceRecorder/trcObject.o ./TraceRecorder/trcObject.su ./TraceRecorder/trcPrint.cyclo ./TraceRecorder/trcPrint.d ./TraceRecorder/trcPrint.o ./TraceRecorder/trcPrint.su ./TraceRecorder/trcRunnable.cyclo ./TraceRecorder/trcRunnable.d ./TraceRecorder/trcRunnable.o ./TraceRecorder/trcRunnable.su ./TraceRecorder/trcSnapshotRecorder.cyclo ./TraceRecorder/trcSnapshotRecorder.d ./TraceRecorder/trcSnapshotRecorder.o ./TraceRecorder/trcSnapshotRecorder.su ./TraceRecorder/trcStackMonitor.cyclo ./TraceRecorder/trcStackMonitor.d ./TraceRecorder/trcStackMonitor.o ./TraceRecorder/trcStackMonitor.su ./TraceRecorder/trcStateMachine.cyclo ./TraceRecorder/trcStateMachine.d ./TraceRecorder/trcStateMachine.o ./TraceRecorder/trcStateMachine.su ./TraceRecorder/trcStaticBuffer.cyclo ./TraceRecorder/trcStaticBuffer.d ./TraceRecorder/trcStaticBuffer.o ./TraceRecorder/trcStaticBuffer.su ./TraceRecorder/trcStreamingRecorder.cyclo ./TraceRecorder/trcStreamingRecorder.d ./TraceRecorder/trcStreamingRecorder.o ./TraceRecorder/trcStreamingRecorder.su ./TraceRecorder/trcString.cyclo ./TraceRecorder/trcString.d ./TraceRecorder/trcString.o ./TraceRecorder/trcString.su ./TraceRecorder/trcTask.cyclo ./TraceRecorder/trcTask.d ./TraceRecorder/trcTask.o ./TraceRecorder/trcTask.su ./TraceRecorder/trcTimestamp.cyclo ./TraceRecorder/trcTimestamp.d ./TraceRecorder/trcTimestamp.o ./TraceRecorder/trcTimestamp.su

.PHONY: clean-TraceRecorder

