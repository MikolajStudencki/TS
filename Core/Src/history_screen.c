#include "history_screen.h"
#include "temp_meter.h"
#include "buttons.h"

static void handleDisplayStatusZero(void);
static void handleDisplayStatusOne(void);
static void handleDisplayStatusTwo(void);

static void displayArrowUp(void);
static void displayArrowDown(void);

static void displayCleanHistory(void);
static void displayCheckHistory(void);

static void displayClean(void);
static void displayCancel(void);

static void displayHistoryDetails(void);

static void changeActionStatus(void);

static void decrementSelectedRow(void);
static void incrementSelectedRow(void);

static void decrementHistoryIndex(void);
static void incrementHistoryIndex(void);

static void handleMainHistoryDisplay(void);
static void handleClearHistoryDisplay(void);

static void backToMainHistoryScreen(void);

static Lcd_HandleTypeDef *lcd;

static uint8_t displayStatus = 0;
static uint8_t lastDisplayStatus = 0;

static uint8_t selectedRow = 0;

static uint8_t historyIndex = 0;
static uint8_t maxHistoryIndex = 0;
static temperatureHistory *alarmsHistory;

void historyScreenInit(Lcd_HandleTypeDef *lcd_var)
{
	lcd = lcd_var;
}

void displayHistoryScreen()
{
	switch (displayStatus)
	{
		case 0:
			handleDisplayStatusZero();
			break;
		case 1:
			handleDisplayStatusOne();
			break;
		case 2:
			handleDisplayStatusTwo();
			break;
	}
}

static void handleDisplayStatusZero()
{
	if (getLastScreenIndex() != Alarms_History_Screen ||
			displayStatus != lastDisplayStatus)
	{
		displayArrowUp();
		displayArrowDown();

		setBtnUpFun(&decrementSelectedRow);
		setBtnDownFun(&incrementSelectedRow);

		setBtnLeftFun(&decrementDisplayIndex);
		setBtnRightFun(&incrementDisplayIndex);

		setBtnMidFun(&changeActionStatus);

		Lcd_clear(lcd);
		lastDisplayStatus = 0;
	}

	displayCleanHistory();
	displayCheckHistory();
}

static void handleDisplayStatusOne()
{
	if (displayStatus != lastDisplayStatus)
	{
		Lcd_clear(lcd);
		lastDisplayStatus = 1;

		setBtnUpFun(&decrementSelectedRow);
		setBtnDownFun(&incrementSelectedRow);

		setBtnLeftFun(&doNothing);
		setBtnRightFun(&doNothing);

		setBtnMidFun(&changeActionStatus);
	}

	displayClean();
	displayCancel();
}

static void handleDisplayStatusTwo()
{
	if (displayStatus != lastDisplayStatus)
	{
		Lcd_clear(lcd);
		lastDisplayStatus = 2;

		alarmsHistory = getTemperatureHistory();
		historyIndex = getAlarmsCounter() - 1;
		maxHistoryIndex = getAlarmsCounter() - 1;

		setBtnUpFun(&incrementHistoryIndex);
		setBtnDownFun(&decrementHistoryIndex);

		setBtnLeftFun(&doNothing);
		setBtnRightFun(&doNothing);

		setBtnMidFun(&backToMainHistoryScreen);
	}
	displayHistoryDetails();
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

static void displayCleanHistory()
{
	Lcd_cursor(lcd, 0, 1);
	Lcd_string(lcd, "CLEAN HISTORY");
}

static void displayCheckHistory()
{
	Lcd_cursor(lcd, 1, 1);
	Lcd_string(lcd, "CHECK HISTORY");
}

static void displayClean()
{
	Lcd_cursor(lcd, 0, 1);
	Lcd_string(lcd, "CLEAN ");
	Lcd_int(lcd, getAlarmsCounter());
}

static void displayCancel()
{
	Lcd_cursor(lcd, 1, 1);
	Lcd_string(lcd, "CANCEL");
}

static void displayHistoryDetails()
{
	if (getAlarmsCounter() == 0)
	{
		Lcd_cursor(lcd, 0, 3);
		Lcd_string(lcd, "NO ALARMS");
		Lcd_cursor(lcd, 1, 3);
		Lcd_string(lcd, "RECORDED");
	}
	else
	{
		Lcd_cursor(lcd, 0, 1);
		Lcd_displayTemperature(lcd, alarmsHistory[historyIndex].alarmTemperature, 'n');
		Lcd_cursor(lcd, 0, 6);
		Lcd_displayDate(lcd,
				alarmsHistory[historyIndex].alarmDate.year,
				alarmsHistory[historyIndex].alarmDate.month,
				alarmsHistory[historyIndex].alarmDate.day);
		Lcd_cursor(lcd, 1, 8);
		Lcd_displayTime(lcd,
				alarmsHistory[historyIndex].alarmDate.hour,
				alarmsHistory[historyIndex].alarmDate.minute,
				alarmsHistory[historyIndex].alarmDate.second);
		Lcd_cursor(lcd, 1, 1);
		Lcd_int(lcd, alarmsHistory[historyIndex].alarmDuration / 1000);
		Lcd_string(lcd, "s");
	}
}

static void decrementSelectedRow()
{
	selectedRow = 0;
}

static void incrementSelectedRow()
{
	selectedRow = 1;
}

static void incrementHistoryIndex()
{
	if (historyIndex < maxHistoryIndex)
	{
		++historyIndex;
	}
}

static void decrementHistoryIndex()
{
	if (historyIndex > 0)
	{
		--historyIndex;
	}
}

static void changeActionStatus()
{

	switch (displayStatus)
	{
		case 0:
			handleMainHistoryDisplay();
			break;
		case 1:
			handleClearHistoryDisplay();
			break;
	}
}

static void handleMainHistoryDisplay()
{
	switch (selectedRow)
	{
		case 0:
			displayStatus = 1;
			selectedRow = 0;
			break;
		case 1:
			displayStatus = 2;
			break;
	}

}

static void handleClearHistoryDisplay()
{
	switch (selectedRow)
	{
		case 0:
			clearCounterHistory();
			break;
		case 1:
			displayStatus = 0;
			selectedRow = 0;
			break;
	}
}

static void backToMainHistoryScreen()
{
	displayStatus = 0;
}
