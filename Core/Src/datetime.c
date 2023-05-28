/*!
 *	\file datetime.c
 * 	\brief This file contains private and public variables, prototypes, functions for date-time operations.
 *
 *	This file contains private set of prototypes, variables and functions and public implementation
 *	of prototypes from file 'datatime.h'.
 *
 *  Created 19/05/2023
 *  \author Mikołaj Haglauer
 */

/*!
 *	\var static dateTime dateTimeMap[6]
 * 	\brief Array of dateTime variables.
 *
 * 	Map indexes: [0] second, [1] minute, [2] hour, [3] day, [4] month, [5] year.
 */

/*!
 *	\var static dateTime *second
 * 	\brief Pointer to a "second" dateTime variable in dateTimeMap.
 */

/*!
 *	\var static dateTime *minute
 * 	\brief Pointer to a "minute" dateTime variable in dateTimeMap.
 */

/*!
 *	\var static dateTime *hour
 * 	\brief Pointer to a "hour" dateTime variable in dateTimeMap.
 */

/*!
 *	\var static dateTime *day
 * 	\brief Pointer to a "day" dateTime variable in dateTimeMap.
 */

/*!
 *	\var static dateTime *month
 * 	\brief Pointer to a "month" dateTime variable in dateTimeMap.
 */

/*!
 *	\var static dateTime *year
 * 	\brief Pointer to a "year" dateTime variable in dateTimeMap.
 */

/*!
 *	\var static uint32_t end_time
 * 	\brief Value of end time of measure in cycleThroughSecond function.
 */

/*!
 *	\var static uint32_t start_time
 * 	\brief Value of started time of measure in cycleThroughSecond function.
 */

/*!
 *	\fn static void displayDateTimePart(Lcd_HandleTypeDef *lcd, dateTime *dt_var)
 *	\brief Function used to display parts of the date.
 *	\param lcd Pointer to LCD display.
 *	\param dt_var Pointer to displayed dateTime variable.
 */

/*!
 *	\fn static void checkDateTime(dateTime *dt_var, dateTime *i_dt_var)
 *  \brief Function used to check and increment parts of the dateTime.
 *	\param dt_var Pointer to checked value.
 *	\param i_dt_var Pointer to next in size dateTime variable incremented value.
 */

/*!
 *	\fn static void iterateDateTime(void)
 *	\brief Function used to iterate through dateTime variables to correctly estimate and set date and time.
 *
 *	Needs cycleThroughSecond function to cycle through this method every time a second passes.
 */

#include "datetime.h"

/************************************** Private function prototypes **************************************/
static void displayDateTimePart(Lcd_HandleTypeDef *lcd, uint16_t dt_var);
static void checkDateTime(dateTime *dt_var, dateTime *i_dt_var);
static void iterateDateTime(void);

/************************************** Private variables **************************************/
static dateTime dateTimeMap[6] =
{
		{
				.currentValue = 30,
				.maxValue = 59,
				.minValue = 0
		},
		{
				.currentValue = 59,
				.maxValue = 59,
				.minValue = 0
		},
		{
				.currentValue = 23,
				.maxValue = 23,
				.minValue = 0
		},
		{
				.currentValue = 19,
				.maxValue = 31,
				.minValue = 1
		},
		{
				.currentValue = May,
				.maxValue = 12,
				.minValue = 1
		},
		{
				.currentValue = 2023,
				.maxValue = 9999,
				.minValue = 0
		}

};

static dateTime *second = &dateTimeMap[Second];
static dateTime *minute = &dateTimeMap[Minute];
static dateTime *hour = &dateTimeMap[Hour];
static dateTime *day = &dateTimeMap[Day];
static dateTime *month = &dateTimeMap[Month];
static dateTime *year = &dateTimeMap[Year];

static uint32_t end_time;
static uint32_t start_time;

/************************************** Public functions **************************************/
void Lcd_displayTime(Lcd_HandleTypeDef *lcd, uint8_t hour_var, uint8_t minute_var, uint8_t second_var)
{
	displayDateTimePart(lcd, hour_var);
	Lcd_string(lcd, "-");

	displayDateTimePart(lcd, minute_var);
	Lcd_string(lcd, "-");

	displayDateTimePart(lcd, second_var);
}

void Lcd_displayDate(Lcd_HandleTypeDef *lcd, uint16_t year_var, uint8_t month_var, uint8_t day_var)
{
	displayDateTimePart(lcd, year_var);
	Lcd_string(lcd, "-");

	displayDateTimePart(lcd, month_var);
	Lcd_string(lcd, "-");

	displayDateTimePart(lcd, day_var);
}

dateTime getDateTimeByKey(dateTimeKey key)
{
	return dateTimeMap[key];
}

void setDateTimeByKey(dateTimeKey key, uint16_t var)
{
	dateTimeMap[key].currentValue = var;
}

void setAll(uint16_t year_var, uint16_t month_var, uint16_t day_var, uint16_t hour_var, uint16_t minute_var, uint16_t second_var)
{
	year->currentValue = year_var;
	month->currentValue = month_var;
	day->currentValue = day_var;
	hour->currentValue = hour_var;
	minute->currentValue = minute_var;
	second->currentValue = second_var;
}

void cycleThroughSecond()
{
	end_time = HAL_GetTick();

	if (end_time - start_time >= 1000)
	{
		iterateDateTime();
		start_time = end_time;
	}
}

uint8_t getMaxDaysByMonth(monthsKey month_key)
{
	switch (month_key)
	{
		case 2:
			if (((year->currentValue % 4 == 0) && (year->currentValue % 100 != 0)) ||
				(year->currentValue % 400 == 0))
			{
				return 29;
			}
			return 28;
		case 4:
		case 6:
		case 8:
		case 10:
		case 12:
			return 30;
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 11:
		default:
			return 31;
	}
}

/************************************** Private functions **************************************/
static void iterateDateTime()
{
	++second->currentValue;
	for (int i = 0; i < 5; i++)
	{
		checkDateTime(&dateTimeMap[i], &dateTimeMap[i + 1]);
	}

	if (day->currentValue == 1)
	{
		day->maxValue = getMaxDaysByMonth(month->currentValue);
	}
}

static void checkDateTime(dateTime *dt_var, dateTime *i_dt_var)
{
	if (dt_var->currentValue > dt_var->maxValue)
	{
		dt_var->currentValue = dt_var->minValue;
		++i_dt_var->currentValue;
	}
}

static void displayDateTimePart(Lcd_HandleTypeDef *lcd, uint16_t dt_var)
{
	if (dt_var < 10)
	{
		Lcd_int(lcd, 0);
	}
	Lcd_int(lcd, dt_var);
}
