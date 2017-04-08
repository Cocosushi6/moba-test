################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/common/objects/object.cpp 

OBJS += \
./src/common/objects/object.o 

CPP_DEPS += \
./src/common/objects/object.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/objects/%.o: ../src/common/objects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


