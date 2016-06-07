################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../handler.cpp \
../main.cpp \
../server.cpp \
../shared_data.cpp 

OBJS += \
./handler.o \
./main.o \
./server.o \
./shared_data.o 

CPP_DEPS += \
./handler.d \
./main.d \
./server.d \
./shared_data.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


