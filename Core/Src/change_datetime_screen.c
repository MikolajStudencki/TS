#include "change_datetime_screen.h"
#include "datetime.h"

static void displayDate(Lcd_HandleTypeDef *lcd);
static void displayTime(Lcd_HandleTypeDef *lcd);
static void displayArrowUp(Lcd_HandleTypeDef *lcd);
static void displayArrowDown(Lcd_HandleTypeDef *lcd);

//static uint8_t selectedIndexX;
//static uint8_t selectedIndexY;
//static uint8_t isChangeToggled;

void displayChangeDateTimeScreen(Lcd_HandleTypeDef *lcd)
{
	displayArrowUp(lcd);
	displayArrowDown(lcd);
	displayDate(lcd);
	displayTime(lcd);
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
