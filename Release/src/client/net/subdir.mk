################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/client/net/client.cpp \
../src/client/net/packet.cpp 

OBJS += \
./src/client/net/client.o \
./src/client/net/packet.o 

CPP_DEPS += \
./src/client/net/client.d \
./src/client/net/packet.d 


# Each subdirectory must supply rules for building sources it contributes
src/client/net/%.o: ../src/client/net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


