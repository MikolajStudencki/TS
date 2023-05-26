#include "change_datetime_screen.h"

static void displayDate(Lcd_HandleTypeDef *lcd);
static void displayTime(Lcd_HandleTypeDef *lcd);
static void displayArrowUp(Lcd_HandleTypeDef *lcd);
static void displayArrowDown(Lcd_HandleTypeDef *lcd);
static void blink(Lcd_HandleTypeDef *lcd, uint8_t col_var, uint8_t row);

static uint32_t end_time;
static uint32_t start_time;

//static uint8_t selectedIndexX;
//static uint8_t selectedIndexY;
//static uint8_t isChangeToggled;

void displayChangeDateTimeScreen(Lcd_HandleTypeDef *lcd)
{
	displayArrowUp(lcd);
	displayArrowDown(lcd);
	blink(lcd, 11, 0);
	Lcd_cursor(lcd, 0, 0);
	displayDate(lcd);
	displayTime(lcd);
}

static void blink(Lcd_HandleTypeDef *lcd, uint8_t col_var, uint8_t row)
{
	end_time = HAL_GetTick();

	if(end_time - start_time >= 100)
	{
		for(uint8_t col = 1;col<col_var;col++)
			{
				Lcd_cursor(lcd, row, col);
				Lcd_string(lcd," ");
			}
		start_time = end_time;
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
