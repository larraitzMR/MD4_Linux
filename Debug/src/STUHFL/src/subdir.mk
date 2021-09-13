################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/STUHFL/src/stuhfl.c \
../src/STUHFL/src/stuhfl_al.c \
../src/STUHFL/src/stuhfl_dl.c \
../src/STUHFL/src/stuhfl_evalAPI_host.c \
../src/STUHFL/src/stuhfl_helpers.c \
../src/STUHFL/src/stuhfl_log.c \
../src/STUHFL/src/stuhfl_pl.c \
../src/STUHFL/src/stuhfl_sl.c 

OBJS += \
./src/STUHFL/src/stuhfl.o \
./src/STUHFL/src/stuhfl_al.o \
./src/STUHFL/src/stuhfl_dl.o \
./src/STUHFL/src/stuhfl_evalAPI_host.o \
./src/STUHFL/src/stuhfl_helpers.o \
./src/STUHFL/src/stuhfl_log.o \
./src/STUHFL/src/stuhfl_pl.o \
./src/STUHFL/src/stuhfl_sl.o 

C_DEPS += \
./src/STUHFL/src/stuhfl.d \
./src/STUHFL/src/stuhfl_al.d \
./src/STUHFL/src/stuhfl_dl.d \
./src/STUHFL/src/stuhfl_evalAPI_host.d \
./src/STUHFL/src/stuhfl_helpers.d \
./src/STUHFL/src/stuhfl_log.d \
./src/STUHFL/src/stuhfl_pl.d \
./src/STUHFL/src/stuhfl_sl.d 


# Each subdirectory must supply rules for building sources it contributes
src/STUHFL/src/%.o: ../src/STUHFL/src/%.c src/STUHFL/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -DPOSIX -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


