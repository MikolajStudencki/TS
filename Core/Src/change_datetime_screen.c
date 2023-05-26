#include "change_datetime_screen.h"

typedef void (*DisplayFunction)(Lcd_HandleTypeDef*);

static void displayDate(Lcd_HandleTypeDef *lcd);
static void displayTime(Lcd_HandleTypeDef *lcd);
static void displayArrowUp(Lcd_HandleTypeDef *lcd);
static void displayArrowDown(Lcd_HandleTypeDef *lcd);
static void blink(Lcd_HandleTypeDef *lcd, uint8_t row, uint8_t col, uint32_t length, DisplayFunction display_var);

static uint32_t end_time;
static uint32_t start_time;
static uint8_t counter = 0;

//static uint8_t selectedIndexX;
//static uint8_t selectedIndexY;
//static uint8_t isChangeToggled;

void displayChangeDateTimeScreen(Lcd_HandleTypeDef *lcd)
{
	displayArrowUp(lcd);
	displayArrowDown(lcd);
	blink(lcd, 0, 1, 11, displayDate);
	displayTime(lcd);
}

static void blink(Lcd_HandleTypeDef *lcd, uint8_t row, uint8_t col, uint32_t length, DisplayFunction display_var)
{
	char emptyCharArray[length];
	end_time = HAL_GetTick();

	for (int i = 0; i < length; i++)
	{
		emptyCharArray[i] = ' ';
	}
	emptyCharArray[length] = '\0';

	if(end_time - start_time >= 1000)
	{
		switch(counter)
		{
			case 0:
			{
				display_var(lcd);
				start_time = end_time;
				counter++;
				break;
			}
			case 3:
			{
				counter = 0;
				break;
			}
			default:
			{
				Lcd_cursor(lcd, row, col);
				Lcd_string(lcd, emptyCharArray);
				counter++;
				break;
			}
		}

	}
}

static void displayDate(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 0, 1);
	Lcd_displayDate(lcd,
			getDateTimeByKey(Year).currentValue,
			getDateTimeByKey(Month).currentValue,
			getDateTimeByKey(Day).currentValue);

}

static void displayTime(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 1, 1);
	Lcd_displayTime(lcd,
			getDateTimeByKey(Hour).currentValue,
			getDateTimeByKey(Minute).currentValue,
			getDateTimeByKey(Second).currentValue);
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
