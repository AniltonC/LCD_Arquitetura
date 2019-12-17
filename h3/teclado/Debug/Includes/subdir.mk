################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Includes/mkl_HC06BluetoothSlave.cpp \
../Includes/mkl_UARTInterrupt.cpp \
../Includes/mkl_UARTPort.cpp 

OBJS += \
./Includes/mkl_HC06BluetoothSlave.o \
./Includes/mkl_UARTInterrupt.o \
./Includes/mkl_UARTPort.o 

CPP_DEPS += \
./Includes/mkl_HC06BluetoothSlave.d \
./Includes/mkl_UARTInterrupt.d \
./Includes/mkl_UARTPort.d 


# Each subdirectory must supply rules for building sources it contributes
Includes/%.o: ../Includes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


