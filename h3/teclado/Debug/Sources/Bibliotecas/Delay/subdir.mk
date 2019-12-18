################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/Bibliotecas/Delay/dsf_Delay_ocp.cpp \
../Sources/Bibliotecas/Delay/dsf_TPM_ocp.cpp 

OBJS += \
./Sources/Bibliotecas/Delay/dsf_Delay_ocp.o \
./Sources/Bibliotecas/Delay/dsf_TPM_ocp.o 

CPP_DEPS += \
./Sources/Bibliotecas/Delay/dsf_Delay_ocp.d \
./Sources/Bibliotecas/Delay/dsf_TPM_ocp.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Bibliotecas/Delay/%.o: ../Sources/Bibliotecas/Delay/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


