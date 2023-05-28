#include "temp_meter.h"

static void displayArrowUp(void);
static void displayArrowDown(void);

static Lcd_HandleTypeDef *lcd;

void historyScreenInit(Lcd_HandleTypeDef *lcd_var)
{
	lcd = lcd_var;
}

void displayHistoryScreen(void)
{
	displayArrowUp();
	displayArrowDown();
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
