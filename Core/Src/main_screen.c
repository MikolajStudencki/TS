/*!
 *	\file mainscreen.c
 * 	\brief This file contains public enums and prototypes for buttons operations.
 *
 *  Created 23/05/2023
 *  \author Mikołaj Haglauer
 */

#include "main_screen.h"

static void displayCurrentDate(Lcd_HandleTypeDef *lcd);
static void displayCurrentTime(Lcd_HandleTypeDef *lcd);
static void displayCurrentTemperature(Lcd_HandleTypeDef *lcd, ADC_HandleTypeDef *hadc1);
static void displayAlaramTemperature(Lcd_HandleTypeDef *lcd);
static void refreshTemperatureDisplayEverySecond(Lcd_HandleTypeDef *lcd, ADC_HandleTypeDef *hadc1);

static uint32_t end_time;
static uint32_t start_time;

static int8_t temperature;
static int8_t alarmTemperature;

void displayMainScreen(Lcd_HandleTypeDef *lcd, ADC_HandleTypeDef *hadc1)
{
	displayCurrentTime(lcd);
	displayCurrentDate(lcd);
	refreshTemperatureDisplayEverySecond(lcd, hadc1);
	displayAlaramTemperature(lcd);
}

static void displayCurrentDate(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 0, 6);
	Lcd_displayDate(lcd,
			getDateTimeByKey(Year).currentValue,
			getDateTimeByKey(Month).currentValue,
			getDateTimeByKey(Day).currentValue);
}

static void displayCurrentTime(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 1, 8);
	Lcd_displayTime(lcd,
			getDateTimeByKey(Hour).currentValue,
			getDateTimeByKey(Minute).currentValue,
			getDateTimeByKey(Second).currentValue);

}

static void displayCurrentTemperature(Lcd_HandleTypeDef *lcd, ADC_HandleTypeDef *hadc1)
{
	temperature = getCurrentTemperature(hadc1);

	Lcd_cursor(lcd, 0, 0);
	if (temperature < 10)
	{
		Lcd_int(lcd, 0);
	}
	Lcd_int(lcd, (temperature % 100));

	Lcd_string(lcd, "\x01");
}

static void displayAlaramTemperature(Lcd_HandleTypeDef *lcd)
{
	alarmTemperature = getAlarmTemperature();

	Lcd_cursor(lcd, 1, 0);
	if (alarmTemperature < 10)
	{
		Lcd_int(lcd, 0);
	}
	Lcd_int(lcd, (alarmTemperature % 100));

	Lcd_string(lcd, "\x02");
}

static void refreshTemperatureDisplayEverySecond(Lcd_HandleTypeDef *lcd, ADC_HandleTypeDef *hadc1)
{
	end_time = HAL_GetTick();

	if(end_time - start_time >= 1000)
	{
		displayCurrentTemperature(lcd, hadc1);
		start_time = end_time;
	}
}
