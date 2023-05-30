/*!
 *	\file temp_meter.c
 * 	\brief This file contains public functions implementation, private prototypes, variables and functions implementation for measuring temperature.
 *
 *  \author Sigma
 */

/*!
 *	\fn static void readTemperatureSensorVoltage(void)
 *	\brief Function used to read value of adc and translate it to voltage.
 */

/*!
 *	\fn static void checkAlarmState(void)
 *	\brief Function used to check current alarm state.
 */

/*!
 *	\fn static void addStateToHistory(void)
 *	\brief Function used to add new history details to history array.
 */

/*!
 *	\fn static void checkWhenAlarmTemperatureIsHigherThanTurnOffAlarm(void)
 *	\brief Function used to check alarm state for alarm temperature higher than turn off temperature.
 */

/*!
 *	\fn static void checkWhenAlarmTemperatureIsLowerThanTurnOffAlarm(void)
 *	\brief Function used to check alarm state for alarm temperature lower than turn off temperature.
 */

/*!
 *	\var static const uint16_t adc_range
 *	\brief Constant variable for adc range.
 */

/*!
 *	\var static const float adc_v_ref
 *	\brief Constant variable for adc reference voltage.
 */

/*!
 *	\var static float adc_value
 *	\brief Value of adc read.
 */

/*!
 *	\var static float adc_voltage
 *	\brief Value of translated adc voltage from adc value.
 */

/*!
 *	\var static int8_t temperature
 *	\brief Value of current temperature.
 */

/*!
 *	\var static int8_t alarmTemperature
 *	\brief Value of alarm temperature.
 */

/*!
 *	\var static int8_t alarmTemperature
 *	\brief Value of turn off temperature temperature.
 */

/*!
 *	\var static uint32_t end_time
 *	\brief Value of time used to measure 1 second.
 */

/*!
 *	\var static uint32_t start_time
 *	\brief Value of time used to measure 1 second.
 */

/*!
 *	\var static uint8_t alarmState
 *	\brief Value of current alarm state.
 */

/*!
 *	\var static uint8_t lastAlarmState
 *	\brief Value of last alarm state.
 */

/*!
 *	\var static uint16_t alarmsCounter
 *	\brief Value of alarms counted.
 */

/*!
 *	\var static temperatureHistory *alarmsHistory
 *	\brief Array containing details for alarms history.
 */

/*!
 *	\var static uint32_t timer
 *	\brief Timer counting how many seconds did alarm continue.
 */

/*!
 *	\var static Lcd_HandleTypeDef *lcd
 *	\brief Pointer to lcd display.
 */

/*!
 *	\var static ADC_HandleTypeDef *hadc1
 *	\brief Pointer to adc.
 */

#include "temp_meter.h"
#include "stdlib.h"

static void readTemperatureSensorVoltage(void);

static void checkAlarmState(void);
static void addStateToHistory(void);

static void checkWhenAlarmTemperatureIsHigherThanTurnOffAlarm(void);
static void checkWhenAlarmTemperatureIsLowerThanTurnOffAlarm(void);

static const uint16_t adc_range = 4095;
static const float adc_v_ref = 3.3;
static float adc_value;
static float adc_voltage;

static int8_t temperature;
static int8_t alarmTemperature = 28;
static int8_t turnOff_alarmTemperature = 25;

static uint32_t end_time;
static uint32_t start_time;

static uint8_t alarmState = 0;
static uint8_t lastAlarmState = 0;

static uint16_t alarmsCounter = 0;
static temperatureHistory *alarmsHistory;
static uint32_t timer;

static Lcd_HandleTypeDef *lcd;
static ADC_HandleTypeDef *hadc1;

static char *celDisplayChar = "\x01";

void tempMeterInit(Lcd_HandleTypeDef *lcd_var, ADC_HandleTypeDef *hadc1_var)
{
	lcd = lcd_var;
	hadc1 = hadc1_var;
	alarmsHistory = malloc(alarmsCounter * sizeof (temperatureHistory));
}

int8_t getCurrentTemperature()
{
	readTemperatureSensorVoltage();
	temperature = 100 - (50 * adc_voltage);
	return temperature;
}

void setAlarmTemperature(int8_t alarmTemperature_var)
{
	alarmTemperature = alarmTemperature_var;
}

int8_t getAlarmTemperature()
{
	return alarmTemperature;
}

void setTurnOffAlarmTemperature(int8_t turnOff_alarmTemperature_var)
{
	turnOff_alarmTemperature = turnOff_alarmTemperature_var;
}

int8_t getTurnOffAlarmTemperature()
{
	return turnOff_alarmTemperature;
}

void Lcd_displayTemperature(Lcd_HandleTypeDef *lcd_var, int8_t temp_var, char tempType)
{
	if (tempType == 'a')
	{
		celDisplayChar = "\x02";
	}
	else
	{
		celDisplayChar = "\x01";
	}

	if (temp_var < -9)
	{
		Lcd_int(lcd_var, temp_var);
		Lcd_string(lcd_var, celDisplayChar);
	}
	else if (temp_var < 0)
	{
		Lcd_string(lcd_var, "-");
		Lcd_int(lcd_var, 0);
		Lcd_int(lcd_var, temp_var * (-1));
		Lcd_string(lcd_var, celDisplayChar);
	}
	else if (temp_var < 10)
	{
		Lcd_int(lcd_var, 0);
		Lcd_int(lcd_var, temp_var);
		Lcd_string(lcd_var, celDisplayChar);
		Lcd_string(lcd_var, " ");
	}
	else
	{
		Lcd_int(lcd_var, temp_var);
		Lcd_string(lcd_var, celDisplayChar);
		Lcd_string(lcd_var, " ");
	}
}

void checkTemperatureState()
{
	if (alarmTemperature > turnOff_alarmTemperature)
	{
		checkWhenAlarmTemperatureIsHigherThanTurnOffAlarm();
	}
	else
	{
		checkWhenAlarmTemperatureIsLowerThanTurnOffAlarm();
	}
	checkAlarmState();
}

void clearCounterHistory()
{
	alarmsCounter = 0;
	alarmsHistory = realloc(alarmsHistory, alarmsCounter * sizeof (temperatureHistory));
}

uint16_t getAlarmsCounter()
{
	return alarmsCounter;
}

temperatureHistory *getTemperatureHistory()
{
	return alarmsHistory;
}

static void checkWhenAlarmTemperatureIsHigherThanTurnOffAlarm()
{
	if (getCurrentTemperature() >= alarmTemperature)
	{
		if (lastAlarmState == 0)
		{
			addStateToHistory();
		}

		alarmState = 1;
		lastAlarmState = 1;
		timer = HAL_GetTick();
	}
	else if (getCurrentTemperature() <= turnOff_alarmTemperature)
	{
		if (lastAlarmState == 1)
		{
			alarmsHistory[alarmsCounter - 1].alarmDuration = (HAL_GetTick() - timer) / 1000;
		}

		alarmState = 0;
		lastAlarmState = 0;
	}
	checkAlarmState();
}

static void checkWhenAlarmTemperatureIsLowerThanTurnOffAlarm()
{
	if (getCurrentTemperature() <= alarmTemperature)
	{
		if (lastAlarmState == 0)
		{
			addStateToHistory();
		}

		alarmState = 1;
		lastAlarmState = 1;
		timer = HAL_GetTick();
	}
	else if (getCurrentTemperature() >= turnOff_alarmTemperature)
	{
		if (lastAlarmState == 1)
		{
			alarmsHistory[alarmsCounter - 1].alarmDuration = (HAL_GetTick() - timer) / 1000;
		}

		alarmState = 0;
		lastAlarmState = 0;
	}
	checkAlarmState();
}

static void readTemperatureSensorVoltage()
{
	HAL_ADC_Start(hadc1);
	HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY);
	adc_value = HAL_ADC_GetValue(hadc1);
	adc_voltage = adc_value * (adc_v_ref / adc_range);
}

static void checkAlarmState()
{
	if (alarmState == 1)
	{
		end_time = HAL_GetTick();

		if(end_time - start_time >= 100)
		{
			if (HAL_GPIO_ReadPin(LD5_GPIO_Port, LD5_Pin) == GPIO_PIN_SET)
			{
				HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
			}
			start_time = end_time;
		}
	}
	else
	{
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
	}
}

static void addStateToHistory()
{
	++alarmsCounter;
	alarmsHistory = realloc(alarmsHistory, alarmsCounter * sizeof (temperatureHistory));

	alarmsHistory[alarmsCounter - 1].alarmTemperature = alarmTemperature;
	alarmsHistory[alarmsCounter - 1].alarmDate.year = getDateTimeByKey(Year).currentValue;
	alarmsHistory[alarmsCounter - 1].alarmDate.month = getDateTimeByKey(Month).currentValue;
	alarmsHistory[alarmsCounter - 1].alarmDate.day = getDateTimeByKey(Day).currentValue;
	alarmsHistory[alarmsCounter - 1].alarmDate.hour = getDateTimeByKey(Hour).currentValue;
	alarmsHistory[alarmsCounter - 1].alarmDate.minute = getDateTimeByKey(Minute).currentValue;
	alarmsHistory[alarmsCounter - 1].alarmDate.second = getDateTimeByKey(Second).currentValue;
	alarmsHistory[alarmsCounter - 1].alarmDuration = 0;
}
