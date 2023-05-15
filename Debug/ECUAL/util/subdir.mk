################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ECUAL/util/DWT_Delay.cpp 

OBJS += \
./ECUAL/util/DWT_Delay.o 

CPP_DEPS += \
./ECUAL/util/DWT_Delay.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/util/%.o ECUAL/util/%.su ECUAL/util/%.cyclo: ../ECUAL/util/%.cpp ECUAL/util/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ECUAL-2f-util

clean-ECUAL-2f-util:
	-$(RM) ./ECUAL/util/DWT_Delay.cyclo ./ECUAL/util/DWT_Delay.d ./ECUAL/util/DWT_Delay.o ./ECUAL/util/DWT_Delay.su

.PHONY: clean-ECUAL-2f-util

