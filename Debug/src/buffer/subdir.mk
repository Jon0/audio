################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/buffer/BaseBuffer.cpp \
../src/buffer/GenBuffer.cpp \
../src/buffer/Random.cpp \
../src/buffer/TestBuffer.cpp \
../src/buffer/WavBuffer.cpp 

OBJS += \
./src/buffer/BaseBuffer.o \
./src/buffer/GenBuffer.o \
./src/buffer/Random.o \
./src/buffer/TestBuffer.o \
./src/buffer/WavBuffer.o 

CPP_DEPS += \
./src/buffer/BaseBuffer.d \
./src/buffer/GenBuffer.d \
./src/buffer/Random.d \
./src/buffer/TestBuffer.d \
./src/buffer/WavBuffer.d 


# Each subdirectory must supply rules for building sources it contributes
src/buffer/%.o: ../src/buffer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


