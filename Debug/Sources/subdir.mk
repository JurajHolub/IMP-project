################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/buttons.c \
../Sources/display.c \
../Sources/lptmr0.c \
../Sources/main.c 

OBJS += \
./Sources/buttons.o \
./Sources/display.o \
./Sources/lptmr0.o \
./Sources/main.o 

C_DEPS += \
./Sources/buttons.d \
./Sources/display.d \
./Sources/lptmr0.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


