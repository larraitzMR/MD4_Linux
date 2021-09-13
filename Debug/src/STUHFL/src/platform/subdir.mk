################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/STUHFL/src/platform/stuhfl_bl_posix.c \
../src/STUHFL/src/platform/stuhfl_platform.c 

OBJS += \
./src/STUHFL/src/platform/stuhfl_bl_posix.o \
./src/STUHFL/src/platform/stuhfl_platform.o 

C_DEPS += \
./src/STUHFL/src/platform/stuhfl_bl_posix.d \
./src/STUHFL/src/platform/stuhfl_platform.d 


# Each subdirectory must supply rules for building sources it contributes
src/STUHFL/src/platform/%.o: ../src/STUHFL/src/platform/%.c src/STUHFL/src/platform/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -DPOSIX -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


