################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HKPD_program.c \
../HLCD_program.c \
../KEYPAD_program.c \
../MADC_program.c \
../MDIO_program.c \
../MGIE_program.c \
../MTIM_program.c \
../MUART_program.c \
../main.c 

OBJS += \
./HKPD_program.o \
./HLCD_program.o \
./KEYPAD_program.o \
./MADC_program.o \
./MDIO_program.o \
./MGIE_program.o \
./MTIM_program.o \
./MUART_program.o \
./main.o 

C_DEPS += \
./HKPD_program.d \
./HLCD_program.d \
./KEYPAD_program.d \
./MADC_program.d \
./MDIO_program.d \
./MGIE_program.d \
./MTIM_program.d \
./MUART_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


