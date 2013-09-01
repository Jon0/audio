################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/process/Process.cpp \
../src/process/Vector.cpp 

OBJS += \
./src/process/Process.o \
./src/process/Vector.o 

CPP_DEPS += \
./src/process/Process.d \
./src/process/Vector.d 


# Each subdirectory must supply rules for building sources it contributes
src/process/%.o: ../src/process/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


