#include "change_datetime_screen.h"
#include "datetime.h"

static uint8_t row_index = 0;
static const uint8_t max_row_index = 1;
static uint8_t date_position = 0;
static uint8_t time_position = 0;
static dateTimeKey key;
static dateTime date;
static uint8_t was_changed = 0;
static uint16_t year;
static uint16_t month;
static uint16_t day;
static uint16_t hour;
static uint16_t minute;
static uint16_t second;

static void displayDate(Lcd_HandleTypeDef *lcd);
static void displayTime(Lcd_HandleTypeDef *lcd);
static void displayArrowUp(Lcd_HandleTypeDef *lcd);
static void displayArrowDown(Lcd_HandleTypeDef *lcd);
void incrementDisplayIndex(void);
void decrementDisplayIndex(void);

//static uint8_t selectedIndexX;
//static uint8_t selectedIndexY;
//static uint8_t isChangeToggled;

static void incrementRowIndex()
{
	if (row_index == max_row_index)
	{
		row_index = 0;
	}
	else
	{
		++row_index;
	}
}

static void incrementValue()
{
	date = getDateTimeByKey(key);
	switch(key)
	{
		case Second:
			if(second == date.maxValue)
			{
				second = date.minValue;
			}
			else
			{
				++second;
			}
			break;
		default:
			if(date.currentValue == date.maxValue)
			{
				setDateTimeByKey(key, date.minValue);
			}
			else
			{
				setDateTimeByKey(key, ++date.currentValue);
			}
			break;
	}
}

static void decrementValue()
{
	date = getDateTimeByKey(key);
	switch(key)
	{
		case Second:
			if(second == date.minValue)
			{
				second = date.maxValue;
			}
			else
			{
				--second;
			}
			break;

		default:
			if(date.currentValue == date.minValue)
			{
				setDateTimeByKey(key, date.maxValue);
			}
			else
			{
				setDateTimeByKey(key, --date.currentValue);
			}
			break;
	}
}

static void dateChange()
{

	set_btn_up_fun(&incrementValue);
	set_btn_down_fun(&decrementValue);
	++date_position;
	++time_position;
}

static void doNothing() {}

void displayChangeDateTimeScreen(Lcd_HandleTypeDef *lcd)
{
	if(date_position == 0 && time_position == 0)
	{
		set_btn_up_fun(&incrementRowIndex);
		set_btn_down_fun(&incrementRowIndex);
	}
	set_btn_mid_fun(&dateChange);
	if(was_changed == 0)
	{
		year = getDateTimeByKey(Year).currentValue;
		month = getDateTimeByKey(Month).currentValue;
		day = getDateTimeByKey(Day).currentValue;
		hour = getDateTimeByKey(Hour).currentValue;
		minute = getDateTimeByKey(Minute).currentValue;
		second = getDateTimeByKey(Second).currentValue;
	}
	displayArrowUp(lcd);
	displayArrowDown(lcd);
	callFunctionByButtonPushed();
	switch (row_index)
	{
		case 0:
			time_position = 0;
			switch(date_position)
			{
				case 0:
					Lcd_blink(lcd, 0, 1, 10, displayDate);
					displayTime(lcd);
					break;
				case 1:
					key = Year;
					Lcd_blink(lcd, 0, 1, 4, displayDate);
					displayTime(lcd);
					break;
				case 2:
					key = Month;
					Lcd_blink(lcd, 0, 6, 2, displayDate);
					displayTime(lcd);
					break;
				case 3:
					key = Day;
					Lcd_blink(lcd, 0, 9, 2, displayDate);
					displayTime(lcd);
					break;
				default:
					was_changed = 1;
					if(was_changed == 1)
					{
						setAll(year, month, day, hour, minute, second);
						was_changed = 0;
					}
					date_position = 0;
					time_position = 0;
					break;
			}
			break;
		case 1:
			date_position = 0;
			switch(time_position)
			{
				case 0:
					displayDate(lcd);
					Lcd_blink(lcd, 1, 1, 8, displayTime);
					break;
				case 1:
					key = Hour;
					displayDate(lcd);
					Lcd_blink(lcd, 1, 1, 2, displayTime);
					break;
				case 2:
					key = Minute;
					displayDate(lcd);
					Lcd_blink(lcd, 1, 4, 2, displayTime);
					break;
				case 3:
					key = Second;
					displayDate(lcd);
					Lcd_blink(lcd, 1, 7, 2, displayTime);
					was_changed = 1;
					break;
				default:
					if(was_changed == 1)
					{
						setAll(year, month, day, hour, minute, second);
						was_changed = 0;
					}
					time_position = 0;
					date_position = 0;
					break;
			}
			break;
	}
}

static void displayDate(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 0, 1);
	Lcd_displayDate(lcd,
		year,
		month,
		day);

}

static void displayTime(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 1, 1);
	Lcd_displayDate(lcd,
		hour,
		minute,
		second);
}

static void displayArrowUp(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 0, 0);
	Lcd_string(lcd, "\x03");
}

static void displayArrowDown(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 1, 0);
	Lcd_string(lcd, "\x04");
}
