################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../unused/Playback.cpp \
../unused/Scope.cpp \
../unused/test.cpp 

OBJS += \
./unused/Playback.o \
./unused/Scope.o \
./unused/test.o 

CPP_DEPS += \
./unused/Playback.d \
./unused/Scope.d \
./unused/test.d 


# Each subdirectory must supply rules for building sources it contributes
unused/%.o: ../unused/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


