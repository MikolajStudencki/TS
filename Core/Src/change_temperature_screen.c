#include "change_temperature_screen.h"
#include "temp_meter.h"
#include "buttons.h"
#include "screens_manager.h"

static void handleActionStatusZero(void);
static void handleActionStatusOne(void);

static void displayArrowUp(void);
static void displayArrowDown(void);

static void displayAlarmTemperature(void);
static void displayTurnOffAlarmTemperature(void);

static void setLocalTemperatures(void);

static void changeActionStatus(void);

static void upRowAction(void);
static void downRowAction(void);

static void incrementSelectedTemperatureValue(void);
static void decrementSelectedTemperatureValue(void);

static void blinkOnCursor();

static int8_t alarmTemperature;
static int8_t turnOff_alarmTemperature;
static Lcd_HandleTypeDef *lcd;

static uint8_t cursorRow = 0;

static uint8_t actionStatus = 0;
static uint8_t lastActionStatus = 0;

void changeTemperatureScreenInit(Lcd_HandleTypeDef *lcd_var)
{
	lcd = lcd_var;
	setLocalTemperatures();
}

void displayChangeTemperatureScreen()
{
	if (getLastScreenIndex() != Change_Temperature_Screen)
	{
		displayArrowUp();
		displayArrowDown();
		setBtnUpFun(&upRowAction);
		setBtnDownFun(&downRowAction);
		setBtnMidFun(&changeActionStatus);
	}

	blinkOnCursor();

	if (actionStatus != lastActionStatus)
	{
		switch (actionStatus)
		{
			case 0:
				handleActionStatusZero();
				break;
			case 1:
				handleActionStatusOne();
				break;
		}
	}
}

static void handleActionStatusZero()
{
	lastActionStatus = 0;
	setAlarmTemperature(alarmTemperature);
	setTurnOffAlarmTemperature(turnOff_alarmTemperature);
	setLocalTemperatures();
	setBtnLeftFun(&decrementDisplayIndex);
	setBtnRightFun(&incrementDisplayIndex);
}

static void handleActionStatusOne()
{
	lastActionStatus = 1;
	setBtnLeftFun(&doNothing);
	setBtnRightFun(&doNothing);
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

static void displayAlarmTemperature()
{
	Lcd_cursor(lcd, 0, 1);
	Lcd_displayTemperature(lcd, alarmTemperature, 'a');
}

static void displayTurnOffAlarmTemperature()
{
	Lcd_cursor(lcd, 1, 1);
	Lcd_displayTemperature(lcd, turnOff_alarmTemperature, 'n');
}

static void setLocalTemperatures()
{
	alarmTemperature = getAlarmTemperature();
	turnOff_alarmTemperature = getTurnOffAlarmTemperature();
}

static void changeActionStatus()
{
	switch (actionStatus)
	{
		case 0:
			lastActionStatus = 0;
			actionStatus = 1;
			setBtnUpFun(&incrementSelectedTemperatureValue);
			setBtnDownFun(&decrementSelectedTemperatureValue);
			break;
		case 1:
			lastActionStatus = 1;
			actionStatus = 0;
			setBtnUpFun(&upRowAction);
			setBtnDownFun(&downRowAction);
			break;
	}
}

static void upRowAction()
{
	cursorRow = 0;
}

static void downRowAction()
{
	cursorRow = 1;
}

static void incrementSelectedTemperatureValue()
{
	switch (cursorRow)
	{
		case 0:
			if (alarmTemperature == 99)
			{
				alarmTemperature = -100;
			}
			++alarmTemperature;
			break;
		case 1:
			if (turnOff_alarmTemperature == 99)
			{
				turnOff_alarmTemperature = -100;
			}
			++turnOff_alarmTemperature;
			break;
	}
	Lcd_disableBlink();
}

static void decrementSelectedTemperatureValue()
{
	switch (cursorRow)
	{
		case 0:
			if (alarmTemperature == -99)
			{
				alarmTemperature = 100;
			}
			--alarmTemperature;
			break;
		case 1:
			if (turnOff_alarmTemperature == -99)
			{
				turnOff_alarmTemperature = 100;
			}
			--turnOff_alarmTemperature;
			break;
	}
	Lcd_disableBlink();
}

static void blinkOnCursor()
{
	switch(cursorRow)
	{
		case 0:
			Lcd_blink(lcd, 0, 1, 2, &displayAlarmTemperature);
			displayTurnOffAlarmTemperature();
			break;

		case 1:
			Lcd_blink(lcd, 1, 1, 2, &displayTurnOffAlarmTemperature);
			displayAlarmTemperature();
			break;
	}
}

