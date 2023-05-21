/*!
 *	\file datetime.h
 * 	\brief This file contains public prototypes and structures for date-time.
 *
 *	This file contains public functions for getting, setting and displaying date and time
 *	on LCD display. It also contains structure type for date-time variables.
 *
 *  Created 19/05/2023
 *  \author Mikołaj Haglauer
 */

/*!
 *	\typedef typedef enum dateTimeKey
 *	\brief Type definition for an enum used for easier management of dateTimeMap.
 */

/*!
 *	\typedef typedef struct dateTime
 *	\brief Type definition for a structure used for managing dataTime variables that require having information about it's maximum and minimum values.
 */

/*!
 *	\fn void dateTimeInit(void)
 *	\brief Function used to initialize private dateTime variables with default values.
 */

/*!
 *	\fn void displayTimeLcd(Lcd_HandleTypeDef *lcd)
 *	\brief Function used to display device time on LCD. It takes 6 spaces horizontally and 1 space vertically.
 *
 *	Displays: hh-mm-ss.
 *	\param lcd Pointer to LCD display.
 */

/*!
 *	\fn void displayDateLcd(Lcd_HandleTypeDef *lcd)
 *	\brief Function used to display device date on LCD. It takes 8 spaces horizontally and 1 space vertically.
 *
 *	Displays: YYYY-MM-DD.
 *	\param lcd Pointer to LCD display.
 */

/*!
 *	\fn void cycleThroughSecond(void)
 *  \brief Function used to iterate dateTime variables to increment device date and time based on CPU clocks.
 */

/*!
 *	\fn void setDate(uint16_t year_var, uint8_t month_var, uint8_t day_var)
 *	\brief Function used to set date of the device.
 *	\param year_var Value to set year.
 *	\param month_var Value to set month.
 *	\param day_var Value to set day.
 */

/*!
 *	\fn setTime(uint8_t hour_var, uint8_t minute_var, uint8_t second_var)
 *	\brief Function used to set time of the device.
 *	\param hour_var Value to set hour.
 *	\param minute_var Value to set minute.
 *	\param second_var Value to set second.
 */

/*!
 *	\fn dateTime *getDateTimeByKey(dateTimeKey *key)
 *	\brief Function used to get dateTime variable from dateTimeMap.
 *	\param dateTimeKey Enum key to find in map.
 *	\return dateTime Pointer to a value of a key in the map.
 */

/*!
 *	\fn dateTime *getDateTime(void)
 *	\brief Function used to get map of current values.
 *	\return dateTime Pointer to current information about dateTimeMap variables.
 */

/*!
 *	\fn static uint8_t getMaxDaysByMonth(dateTime *month_var)
 *	\brief Function used to get maximum value of a month.
 *	\param month_var Pointer to checked month.
 *	\return uint8_t Maximum value of inserted month.
 */

#include "lcd.h"

/************************************** Public structures **************************************/
typedef enum {
	Second, //!< Representation of [0] index in dateTimeMap.
	Minute, //!< Representation of [1] index in dateTimeMap.
	Hour, //!< Representation of [2] index in dateTimeMap.
	Month, //!< Representation of [3] index in dateTimeMap.
	Day, //!< Representation of [4] index in dateTimeMap.
	Year //!< Representation of [5] index in dateTimeMap.
} dateTimeKey;

typedef struct
{
	uint16_t currentValue; //!< Current value of dateTime variable.
	uint16_t maxValue; //!< Maximum value of dateTime variable.
	uint8_t minValue; //!< Minimum value of dateTime variable.
} dateTime;

/************************************** Public function prototypes **************************************/
void dateTimeInit(void);
void displayTimeLcd(Lcd_HandleTypeDef *lcd);
void displayDateLcd(Lcd_HandleTypeDef *lcd);
void cycleThroughSecond();
void setDate(uint16_t year_var, uint8_t month_var, uint8_t day_var);
void setTime(uint8_t hour_var, uint8_t minute_var, uint8_t second_var);
dateTime *getDateTimeByKey(dateTimeKey key);
uint8_t getMaxDaysByMonth(dateTime *month_var);
