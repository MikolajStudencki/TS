/*!
 *	\file datetime.c
 * 	\brief This file contains private and public variables, prototypes, functions for date-time
 *
 *	This file contains public functions for getting, setting and displaying date and time
 *	on LCD display. It also contains structure type for date-time variables.
 *
 *  \created 19/05/2023
 *  \author Mikołaj Haglauer
 */

#include "datetime.h"

/************************************** Private function prototypes **************************************/
static void displayDateTimePart(Lcd_HandleTypeDef *lcd, dateTime *dt_Var);
static void checkDateTime(dateTime *dt_Var, dateTime *i_dt_Var);
static uint8_t returnDaysByMonth(dateTime *g_month);
/*!
 *	iterateDateTime function
 *	This function is used to iterate through dateTime variables to correctly
 *	estimate and set date and time.
 *	Needs external loop to cycle through this method every time a second passes.
 */
static void iterateDateTime(void);

/************************************** Private variables **************************************/
static dt_Map dateTimeMap[6] =
{
		{
				.key = "second",
				.dt_Var =
				{
						.currentValue = 30,
						.maxValue = 59,
						.minValue = 0
				}
		},
		{
				.key = "minute",
				.dt_Var =
				{
						.currentValue = 59,
						.maxValue = 59,
						.minValue = 0
				}
		},
		{
				.key = "hour",
				.dt_Var =
				{
						.currentValue = 23,
						.maxValue = 23,
						.minValue = 0
				}
		},
		{
				.key = "day",
				.dt_Var =
				{
						.currentValue = 19,
						.maxValue = 31,
						.minValue = 1
				}
		},
		{
				.key = "month",
				.dt_Var =
				{
						.currentValue = 5,
						.maxValue = 12,
						.minValue = 1
				}
		},
		{
				.key = "year",
				.dt_Var =
				{
						.currentValue = 2023,
						.maxValue = 9999,
						.minValue = 0
				}
		}
};

static dateTime *year = NULL;
static dateTime *month = NULL;
static dateTime *day = NULL;
static dateTime *hour = NULL;
static dateTime *minute = NULL;
static dateTime *second = NULL;

static uint32_t end_time;
static uint32_t start_time;
/************************************** Public functions **************************************/
void dateTimeInit()
{
	year = getDateTimeByKey("year");
	month = getDateTimeByKey("month");
	day = getDateTimeByKey("day");
	hour = getDateTimeByKey("hour");
	minute = getDateTimeByKey("minute");
	second = getDateTimeByKey("second");

	start_time = HAL_GetTick();
}

void displayTimeLcd(Lcd_HandleTypeDef *lcd)
{
	displayDateTimePart(lcd, hour);
	Lcd_string(lcd, "-");

	displayDateTimePart(lcd, minute);
	Lcd_string(lcd, "-");

	displayDateTimePart(lcd, second);
}

void displayDateLcd(Lcd_HandleTypeDef *lcd)
{
	displayDateTimePart(lcd, year);
	Lcd_string(lcd, "-");

	displayDateTimePart(lcd, month);
	Lcd_string(lcd, "-");

	displayDateTimePart(lcd, day);
}

dateTime *getDateTimeByKey(char *key)
{
	for (int i = 0; i < 6; i++)
	{
		if (dateTimeMap[i].key == key)
		{
			return &dateTimeMap[i].dt_Var;
		}
	}
	return &dateTimeMap[0].dt_Var;
}

void setTime(uint8_t s_hour, uint8_t s_minute, uint8_t s_second)
{
	hour->currentValue = s_hour;
	minute->currentValue = s_minute;
	second->currentValue = s_second;
}

void setDate(uint16_t s_year, uint8_t s_month, uint8_t s_day)
{
	year->currentValue = s_year;
	month->currentValue = s_month;
	day->currentValue = s_day;
	day->maxValue = returnDaysByMonth(month);
}

void cycleThroughSecond()
{
	end_time = HAL_GetTick();

	if(end_time - start_time >= 1000)
	{
		iterateDateTime();
		start_time = end_time;
	}
}

/************************************** Private functions **************************************/
static void iterateDateTime()
{
	++second->currentValue;
	for (int i = 0; i < 5; i++)
	{
		checkDateTime(&dateTimeMap[i].dt_Var, &dateTimeMap[i + 1].dt_Var);
	}

	if (day->currentValue == 1)
	{
		day->maxValue = returnDaysByMonth(month);
	}
}

static void checkDateTime(dateTime *dt_Var, dateTime *i_dt_Var)
{
	if (dt_Var->currentValue > dt_Var->maxValue)
	{
		dt_Var->currentValue = dt_Var->minValue;
		++i_dt_Var->currentValue;
	}
}

static void displayDateTimePart(Lcd_HandleTypeDef *lcd, dateTime *dt_Var)
{
	if (dt_Var->currentValue < 10)
	{
		Lcd_int(lcd, 0);
	}
	Lcd_int(lcd, dt_Var->currentValue);
}

static uint8_t returnDaysByMonth(dateTime *g_month)
{
	if (g_month->currentValue == 2) /// If February
	{
		uint16_t yearCV = year->currentValue;
		if (((yearCV % 4 == 0) && (yearCV % 100 != 0)) ||
			(yearCV % 400 == 0)) { /// If leap year return 29 days
			return 29;
		}
		return 28;
	}
	else if ((g_month->currentValue % 2) != 0) /// If odd month return 31 days
	{
		return 31;
	}
	else /// If even month return 30 days
	{
		return 30;
	}
}
