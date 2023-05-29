/*
 * temperature.c
 *
 *  Created on: 20 мая 2023 г.
 *      Author: skrah
 */
#include "temperature.h"

float value;
int temperature;
int alarmTemperature = 36;

void getTemperatureSensorVoltage(ADC_HandleTypeDef *hadc1)
{
	HAL_ADC_Start(hadc1);
	HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY);

	value = HAL_ADC_GetValue(hadc1);

	float voltage = (float)value * 3.3 / 4096;
	temperature = ((voltage - 1.5) / 0.01) + 25.0;
//	temperature = 101 - (50 * ( value / 1200));
//	temperature = 273 - ((value*5*100)/4096);
//	temperature = 100.0 - ((value / 1024.0) * 49.0);
}

void displayCurrentTemperature(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 0, 0);
	Lcd_int(lcd,temperature);
//	if (temperature < 10)
//	{
//		Lcd_int(lcd, 0);
//	}
//	Lcd_int(lcd, (temperature % 100));
//
//	Lcd_string(lcd, "\x01");
}

void displayAlarmTemperature(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 1, 0);
	if (alarmTemperature < 10)
	{
		Lcd_int(lcd, 0);
	}
	Lcd_int(lcd, (alarmTemperature % 100));

	Lcd_string(lcd, "\x01");
	Lcd_string(lcd, "!");

}



