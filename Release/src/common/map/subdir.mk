################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/common/map/world.cpp 

OBJS += \
./src/common/map/world.o 

CPP_DEPS += \
./src/common/map/world.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/map/%.o: ../src/common/map/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


