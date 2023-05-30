#include "screens_manager.h"

static Lcd_HandleTypeDef *lcd;

static const uint8_t max_screen_index = 3;
static uint8_t *screen_index;
static uint8_t *last_screen_index;

void screensManagerInit(Lcd_HandleTypeDef *lcd_var, uint8_t *screen_index_var, uint8_t *last_screen_index_var)
{
	lcd = lcd_var;
	screen_index = screen_index_var;
	last_screen_index = last_screen_index_var;
}

void incrementDisplayIndex()
{
	Lcd_clear(lcd);
	if (*screen_index == max_screen_index)
	{
		*screen_index = 0;
	}
	else
	{
		*screen_index += 1;
	}
}

void decrementDisplayIndex()
{
	Lcd_clear(lcd);
	if (*screen_index == 0)
	{
		*screen_index = max_screen_index;
	}
	else
	{
		*screen_index -= 1;
	}
}

void doNothing() {}

uint8_t getScreenIndex()
{
	return *screen_index;
}

uint8_t getLastScreenIndex()
{
	return *last_screen_index;
}

void setLastScreenIndex(void)
{
	*last_screen_index = *screen_index;
}
