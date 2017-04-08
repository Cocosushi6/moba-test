################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/client/rendering/utils/utils.cpp 

OBJS += \
./src/client/rendering/utils/utils.o 

CPP_DEPS += \
./src/client/rendering/utils/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/client/rendering/utils/%.o: ../src/client/rendering/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


