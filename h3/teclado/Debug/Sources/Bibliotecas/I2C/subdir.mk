################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/Bibliotecas/I2C/mkl_I2C.cpp \
../Sources/Bibliotecas/I2C/mkl_I2CPort.cpp \
../Sources/Bibliotecas/I2C/mkl_LCD.cpp 

OBJS += \
./Sources/Bibliotecas/I2C/mkl_I2C.o \
./Sources/Bibliotecas/I2C/mkl_I2CPort.o \
./Sources/Bibliotecas/I2C/mkl_LCD.o 

CPP_DEPS += \
./Sources/Bibliotecas/I2C/mkl_I2C.d \
./Sources/Bibliotecas/I2C/mkl_I2CPort.d \
./Sources/Bibliotecas/I2C/mkl_LCD.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Bibliotecas/I2C/%.o: ../Sources/Bibliotecas/I2C/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


