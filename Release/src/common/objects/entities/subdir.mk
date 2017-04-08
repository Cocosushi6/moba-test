################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/common/objects/entities/entity.cpp 

OBJS += \
./src/common/objects/entities/entity.o 

CPP_DEPS += \
./src/common/objects/entities/entity.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/objects/entities/%.o: ../src/common/objects/entities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


