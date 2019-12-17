################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/Servicos/Cozimento.cpp \
../Sources/Servicos/EditService.cpp \
../Sources/Servicos/IncrementService.cpp 

OBJS += \
./Sources/Servicos/Cozimento.o \
./Sources/Servicos/EditService.o \
./Sources/Servicos/IncrementService.o 

CPP_DEPS += \
./Sources/Servicos/Cozimento.d \
./Sources/Servicos/EditService.d \
./Sources/Servicos/IncrementService.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Servicos/%.o: ../Sources/Servicos/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


