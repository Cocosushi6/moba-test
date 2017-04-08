################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/server/net/data_manager.cpp \
../src/server/net/server.cpp 

OBJS += \
./src/server/net/data_manager.o \
./src/server/net/server.o 

CPP_DEPS += \
./src/server/net/data_manager.d \
./src/server/net/server.d 


# Each subdirectory must supply rules for building sources it contributes
src/server/net/%.o: ../src/server/net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


