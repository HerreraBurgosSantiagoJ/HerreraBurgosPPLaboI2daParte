################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/aux_main.c \
../Src/errors.c \
../Src/input_lib.c \
../Src/my_system.c \
../Src/sBike.c \
../Src/sServices.c \
../Src/sWorks.c \
../Src/steart.c \
../Src/vallib.c 

OBJS += \
./Src/aux_main.o \
./Src/errors.o \
./Src/input_lib.o \
./Src/my_system.o \
./Src/sBike.o \
./Src/sServices.o \
./Src/sWorks.o \
./Src/steart.o \
./Src/vallib.o 

C_DEPS += \
./Src/aux_main.d \
./Src/errors.d \
./Src/input_lib.d \
./Src/my_system.d \
./Src/sBike.d \
./Src/sServices.d \
./Src/sWorks.d \
./Src/steart.d \
./Src/vallib.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/plainsight/Parcial_Labo_1_Santiago_Joel_Herrera_Burgos/Heathers -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


