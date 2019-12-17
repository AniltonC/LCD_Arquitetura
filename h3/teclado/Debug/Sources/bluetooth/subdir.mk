################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/bluetooth/mkl_HC06BluetoothSlave.cpp \
../Sources/bluetooth/mkl_UARTInterrupt.cpp \
../Sources/bluetooth/mkl_UARTPort.cpp 

OBJS += \
./Sources/bluetooth/mkl_HC06BluetoothSlave.o \
./Sources/bluetooth/mkl_UARTInterrupt.o \
./Sources/bluetooth/mkl_UARTPort.o 

CPP_DEPS += \
./Sources/bluetooth/mkl_HC06BluetoothSlave.d \
./Sources/bluetooth/mkl_UARTInterrupt.d \
./Sources/bluetooth/mkl_UARTPort.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/bluetooth/%.o: ../Sources/bluetooth/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


