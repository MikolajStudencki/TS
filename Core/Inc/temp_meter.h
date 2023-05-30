/*!
 *	\file temp_meter.h
 * 	\brief This file contains public structs and prototypes for measuring temperature.
 *
 *  \author Sigma
 */

/*!
 * 	\typedef struct temperatureHistory
 * 	\brief Type definition for a structure used to manage alarms history.
 */

/*!
 * 	\fn void tempMeterInit(Lcd_HandleTypeDef *lcd_var, ADC_HandleTypeDef *hadc1_var)
 * 	\brief Function used to initialize private variables.
 * 	\param *lcd_var Pointer to lcd display.
 * 	\param *hadc1_var Pointer to adc transmiter.
 */

/*!
 * 	\fn void tempMeterInit(Lcd_HandleTypeDef *lcd_var, ADC_HandleTypeDef *hadc1_var)
 * 	\brief Function used to initialize private variables.
 * 	\param *lcd_var Pointer to lcd display.
 * 	\param *hadc1_var Pointer to adc transmiter.
 */

/*!
 * 	\fn int8_t getCurrentTemperature(void)
 * 	\brief Function used to get current temperature.
 */

/*!
 * 	\fn void setAlarmTemperature(int8_t alarmTemperature_var)
 * 	\brief Function used to set temperature in which alarm occurs.
 */

/*!
 * 	\fn int8_t getAlarmTemperature(void)
 * 	\brief Function used to get current value of alarm temperature.
 */

/*!
 * 	\fn void setTurnOffAlarmTemperature(int8_t turnOff_alarmTemperature_var)
 * 	\brief Function used to set temperature in which alarm will turn off.
 */

/*!
 * 	\fn int8_t getTurnOffAlarmTemperature(void)
 * 	\brief Function used to get current value of turn off alarm temperature.
 */

/*!
 * 	\fn void Lcd_displayTemperature(Lcd_HandleTypeDef *lcd_var, int8_t temp_var, char tempType)
 * 	\brief Function used to display Temperature in standard format up to 2 digits.
 * 	\param *lcd_var Pointer to lcd display.
 * 	\param temp_var Value of displayed temperature.
 * 	\param tempType Type of displayed temperature - either 'a' for alarm, or 'n' for normal.
 */

/*!
 * 	\fn void checkTemperatureState(void)
 * 	\brief Function used to check state of temperature.
 */

/*!
 * 	\fn void checkTemperatureState(void)
 * 	\brief Function used to monitor temperature value.
 */

/*!
 * 	\fn void clearCounterHistory(void)
 * 	\brief Function used to clear history of alarms.
 */

/*!
 * 	\fn uint16_t getAlarmsCounter(void)
 * 	\brief Function used to get current counter of alarms.
 */

/*!
 * 	\fn uint16_t *getTemperatureHistory(void)
 * 	\brief Function used to get array of alarms details from history.
 */

#include "datetime.h"
#include "main.h"
#include "lcd.h"

typedef struct
{
	int8_t alarmTemperature;
	dateUnit alarmDate;
	uint32_t alarmDuration;
} temperatureHistory;

void tempMeterInit(Lcd_HandleTypeDef *lcd_var, ADC_HandleTypeDef *hadc1_var);
int8_t getCurrentTemperature(void);
void setAlarmTemperature(int8_t alarmTemperature_var);
int8_t getAlarmTemperature(void);
void setTurnOffAlarmTemperature(int8_t turnOff_alarmTemperature_var);
int8_t getTurnOffAlarmTemperature(void);
void Lcd_displayTemperature(Lcd_HandleTypeDef *lcd_var, int8_t temp_var, char tempType);
void checkTemperatureState(void);
void clearCounterHistory(void);
uint16_t getAlarmsCounter(void);
temperatureHistory *getTemperatureHistory(void);
