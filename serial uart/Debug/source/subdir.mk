################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/bubble.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/bubble.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/bubble.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DPRINTF_ADVANCED_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/bryanthar/Documents/MCUXpressoIDE_11.7.1_9221/workspace/frdmkl46z_bubble_peripheral/source" -I"/Users/bryanthar/Documents/MCUXpressoIDE_11.7.1_9221/workspace/frdmkl46z_bubble_peripheral" -I"/Users/bryanthar/Documents/MCUXpressoIDE_11.7.1_9221/workspace/frdmkl46z_bubble_peripheral/CMSIS" -I"/Users/bryanthar/Documents/MCUXpressoIDE_11.7.1_9221/workspace/frdmkl46z_bubble_peripheral/drivers" -I"/Users/bryanthar/Documents/MCUXpressoIDE_11.7.1_9221/workspace/frdmkl46z_bubble_peripheral/startup" -I"/Users/bryanthar/Documents/MCUXpressoIDE_11.7.1_9221/workspace/frdmkl46z_bubble_peripheral/utilities" -I"/Users/bryanthar/Documents/MCUXpressoIDE_11.7.1_9221/workspace/frdmkl46z_bubble_peripheral/accel" -I"/Users/bryanthar/Documents/MCUXpressoIDE_11.7.1_9221/workspace/frdmkl46z_bubble_peripheral/board" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/bubble.d ./source/bubble.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

