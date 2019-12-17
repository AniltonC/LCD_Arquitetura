################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/Bibliotecas/Systick/mkl_Systick.cpp \
../Sources/Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.cpp 

OBJS += \
./Sources/Bibliotecas/Systick/mkl_Systick.o \
./Sources/Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.o 

CPP_DEPS += \
./Sources/Bibliotecas/Systick/mkl_Systick.d \
./Sources/Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Bibliotecas/Systick/%.o: ../Sources/Bibliotecas/Systick/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


