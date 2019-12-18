################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/Bibliotecas/GPIO/mkl_GPIO.cpp \
../Sources/Bibliotecas/GPIO/mkl_GPIOInterrupt.cpp \
../Sources/Bibliotecas/GPIO/mkl_GPIOPort.cpp 

OBJS += \
./Sources/Bibliotecas/GPIO/mkl_GPIO.o \
./Sources/Bibliotecas/GPIO/mkl_GPIOInterrupt.o \
./Sources/Bibliotecas/GPIO/mkl_GPIOPort.o 

CPP_DEPS += \
./Sources/Bibliotecas/GPIO/mkl_GPIO.d \
./Sources/Bibliotecas/GPIO/mkl_GPIOInterrupt.d \
./Sources/Bibliotecas/GPIO/mkl_GPIOPort.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Bibliotecas/GPIO/%.o: ../Sources/Bibliotecas/GPIO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


