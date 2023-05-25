#include "stm32f4xx_hal.h"
#include "usb_host.h"
#include "main.h"

int8_t getCurrentTemperature(ADC_HandleTypeDef *hadc1);
int8_t getAlarmTemperature(void);
