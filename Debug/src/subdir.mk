################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/inventory.c \
../src/main.c \
../src/middleware.c \
../src/network.c 

OBJS += \
./src/inventory.o \
./src/main.o \
./src/middleware.o \
./src/network.o 

C_DEPS += \
./src/inventory.d \
./src/main.d \
./src/middleware.d \
./src/network.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -DPOSIX -I"/home/inigo/eclipse-workspace/md4/STUHFL/inc" -I"/home/inigo/eclipse-workspace/md4/STUHFL/inc/platform" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


