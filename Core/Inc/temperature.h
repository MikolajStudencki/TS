/*
 * temperature.h
 *
 *  Created on: 20 мая 2023 г.
 *      Author: skrah
 */
#include "stm32f4xx_hal.h"
#include "main.h"
#include "lcd.h"


void displayCurrentTemperature(Lcd_HandleTypeDef *lcd);
void getTemperatureSensorVoltage(ADC_HandleTypeDef *hadc1);
void displayAlarmTemperature(Lcd_HandleTypeDef *lcd);
