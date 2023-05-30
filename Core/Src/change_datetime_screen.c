#include "change_datetime_screen.h"
#include "datetime.h"
#include "buttons.h"
#include "screens_manager.h"

static void onFirstCall(void);

static void blinkDatePart(void);
static void blinkTimePart(void);

static void onChange(void);

static void displayDate(void);
static void displayTime(void);

static void displayArrowUp(void);
static void displayArrowDown(void);

static void incrementRowIndex(void);
static void decrementRowIndex(void);

static void dateChange(void);

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

static uint8_t row_index = 0;
static uint8_t date_position = 0;
static uint8_t time_position = 0;
static dateTimeKey key;
static uint8_t was_changed = 0;

static Lcd_HandleTypeDef *lcd;

static dateTime *second = &dateTimeMap[Second];
static dateTime *minute = &dateTimeMap[Minute];
static dateTime *hour = &dateTimeMap[Hour];
static dateTime *day = &dateTimeMap[Day];
static dateTime *month = &dateTimeMap[Month];
static dateTime *year = &dateTimeMap[Year];

void changeDateTimeScreenInit(Lcd_HandleTypeDef *lcd_var)
{
	lcd = lcd_var;
}

void displayChangeDateTimeScreen()
{
	dateTimeMap[Day].maxValue = getMaxDaysByMonth(dateTimeMap[Month].currentValue);

	displayArrowUp();
	displayArrowDown();

	onFirstCall();
	setBtnMidFun(&dateChange);

	switch (row_index)
	{
		case 0:
			blinkDatePart();
			break;
		case 1:
			blinkTimePart();
			break;
	}
	onChange();
}

static void onFirstCall()
{
	if(date_position == 0 && time_position == 0)
	{
		setBtnUpFun(&decrementRowIndex);
		setBtnDownFun(&incrementRowIndex);
		setBtnLeftFun(&decrementDisplayIndex);
		setBtnRightFun(&incrementDisplayIndex);

		was_changed = 0;

		if(getLastScreenIndex() != Change_Time_Screen)
		{
			year->currentValue = getDateTimeByKey(Year).currentValue;
			month->currentValue = getDateTimeByKey(Month).currentValue;
			day->currentValue = getDateTimeByKey(Day).currentValue;
			hour->currentValue = getDateTimeByKey(Hour).currentValue;
			minute->currentValue = getDateTimeByKey(Minute).currentValue;
			second->currentValue = getDateTimeByKey(Second).currentValue;
		}
	}

}

static void blinkDatePart()
{
	time_position = 0;
	switch(date_position)
	{
		case 0:
			Lcd_blink(lcd, 0, 1, 10, &displayDate);
			break;
		case 1:
			was_changed = 1;
			key = Year;
			Lcd_blink(lcd, 0, 1, 4, &displayDate);
			break;
		case 2:
			key = Month;
			Lcd_blink(lcd, 0, 6, 2, &displayDate);
			break;
		case 3:
			key = Day;
			Lcd_blink(lcd, 0, 9, 2, &displayDate);
			break;
		default:date_position = 0;
	}
	displayTime();
}

static void blinkTimePart()
{
	date_position = 0;
	switch(time_position)
	{
		case 0:
			Lcd_blink(lcd, 1, 1, 8, &displayTime);
			break;
		case 1:
			was_changed = 1;
			key = Hour;
			Lcd_blink(lcd, 1, 1, 2, &displayTime);
			break;
		case 2:
			key = Minute;
			Lcd_blink(lcd, 1, 4, 2, &displayTime);
			break;
		case 3:
			key = Second;
			Lcd_blink(lcd, 1, 7, 2, &displayTime);
			break;
		default:time_position = 0;
	}
	displayDate();
}

static void onChange()
{
	if (was_changed == 1)
	{
		setAll(year->currentValue, month->currentValue, day->currentValue, hour->currentValue, minute->currentValue, second->currentValue);
	}
}

static void incrementRowIndex()
{
	row_index = 1;
}

static void decrementRowIndex()
{
	row_index = 0;
}

static void incrementValue()
{
    if(dateTimeMap[key].currentValue == dateTimeMap[key].maxValue)
    {
        dateTimeMap[key].currentValue = dateTimeMap[key].minValue;
    }
    else
    {
        ++dateTimeMap[key].currentValue;
    }
    Lcd_disableBlink();
}

static void decrementValue()
{
    if(dateTimeMap[key].currentValue == dateTimeMap[key].minValue)
    {
        dateTimeMap[key].currentValue = dateTimeMap[key].maxValue;
    }
    else
    {
        --dateTimeMap[key].currentValue;
    }
    Lcd_disableBlink();
}

static void dateChange()
{
	setBtnUpFun(&incrementValue);
	setBtnDownFun(&decrementValue);
	setBtnLeftFun(&doNothing);
	setBtnRightFun(&doNothing);
	++date_position;
	++time_position;
}

static void displayDate()
{
	Lcd_cursor(lcd, 0, 1);
	Lcd_displayDate(lcd,
			year->currentValue,
			month->currentValue,
			day->currentValue);

}

static void displayTime()
{
	Lcd_cursor(lcd, 1, 1);
	Lcd_displayDate(lcd,
			hour->currentValue,
			minute->currentValue,
			second->currentValue);
}

static void displayArrowUp()
{
	Lcd_cursor(lcd, 0, 0);
	Lcd_string(lcd, "\x03");
}

static void displayArrowDown()
{
	Lcd_cursor(lcd, 1, 0);
	Lcd_string(lcd, "\x04");
}
