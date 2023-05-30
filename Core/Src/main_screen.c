/*!
 *	\file mainscreen.c
 * 	\brief This file contains public enums and prototypes for buttons operations.
 *
 *  Created 23/05/2023
 *  \author Mikołaj Haglauer
 */

#include "main_screen.h"
#include "temp_meter.h"
#include "screens_manager.h"

static void displayCurrentDate(void);
static void displayCurrentTime(void);
static void displayCurrentTemperature(void);
static void displayAlaramTemperature(void);
static void refreshTemperatureDisplayEverySecond(void);
static void displayAlarmsCounter(void);

static uint32_t end_time;
static uint32_t start_time;

static int8_t temperature;
static int8_t alarmTemperature;

static Lcd_HandleTypeDef *lcd;

void mainScreenInit(Lcd_HandleTypeDef *lcd_var)
{
	lcd = lcd_var;
}

void displayMainScreen()
{
	displayCurrentTime();
	displayCurrentDate();
	refreshTemperatureDisplayEverySecond();
	displayAlaramTemperature();
	displayAlarmsCounter();
}

static void displayCurrentDate()
{
	Lcd_cursor(lcd, 0, 6);
	Lcd_displayDate(lcd,
			getDateTimeByKey(Year).currentValue,
			getDateTimeByKey(Month).currentValue,
			getDateTimeByKey(Day).currentValue);
}

static void displayCurrentTime()
{
	Lcd_cursor(lcd, 1, 8);
	Lcd_displayTime(lcd,
			getDateTimeByKey(Hour).currentValue,
			getDateTimeByKey(Minute).currentValue,
			getDateTimeByKey(Second).currentValue);

}

static void displayCurrentTemperature()
{
	temperature = getCurrentTemperature();
	Lcd_cursor(lcd, 0, 0);
	Lcd_displayTemperature(lcd, temperature, 'n');
}

static void displayAlaramTemperature()
{
	alarmTemperature = getAlarmTemperature();
	Lcd_cursor(lcd, 1, 0);
	Lcd_displayTemperature(lcd, alarmTemperature, 'a');
}

static void displayAlarmsCounter()
{
	Lcd_cursor(lcd, 1, 4);
	Lcd_int(lcd, getAlarmsCounter());
}

static void refreshTemperatureDisplayEverySecond()
{
	end_time = HAL_GetTick();

	if(end_time - start_time >= 1000)
	{
		displayCurrentTemperature();
		start_time = end_time;
	}
}
