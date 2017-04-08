################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/client/rendering/camera.cpp \
../src/client/rendering/mesh.cpp \
../src/client/rendering/model.cpp \
../src/client/rendering/renderer.cpp \
../src/client/rendering/shader.cpp 

OBJS += \
./src/client/rendering/camera.o \
./src/client/rendering/mesh.o \
./src/client/rendering/model.o \
./src/client/rendering/renderer.o \
./src/client/rendering/shader.o 

CPP_DEPS += \
./src/client/rendering/camera.d \
./src/client/rendering/mesh.d \
./src/client/rendering/model.d \
./src/client/rendering/renderer.d \
./src/client/rendering/shader.d 


# Each subdirectory must supply rules for building sources it contributes
src/client/rendering/%.o: ../src/client/rendering/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


