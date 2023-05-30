/*!
 *	\file datetime.h
 * 	\brief This file contains public structures, enums and prototypes for date-time operations.
 *
 *  \author Sigma
 */

/*!
 *	\typedef typedef enum dateTimeKey
 *	\brief Type definition for an enum used for easier management of dateTimeMap.
 */

/*!
 *	\typedef typedef enum monthsKey
 *	\brief Type definition for an enum used for easier management of months in dateTime.
 */

/*!
 *	\typedef typedef struct dateTime
 *	\brief Type definition for a structure used for managing dataTime variables that require
 *	having information about it's maximum and minimum values.
 */

/*!
 *	\typedef typedef struct dateUnit
 *	\brief Type definition for a structure used for storing and managing data of a whole date.
 */

/*!
 *	\fn void Lcd_displayTime(Lcd_HandleTypeDef *lcd, uint8_t hour_var, uint8_t minute_var, uint8_t second_var)
 *	\brief Function used to display time on lcd in default format of hh-mm-ss.
 *	\param *lcd Pointer to LCD display.
 *	\param hour_var Value of displayed hour.
 *	\param minute_var Value of displayed minute.
 *	\param second_var Value of displayed second.
 */

/*!
 *	\fn void Lcd_displayDate(Lcd_HandleTypeDef *lcd, uint16_t year_var, uint8_t month_var, uint8_t day_var)
 *	\brief Function used to display date on lcd in default format of YYYY-MM-DD.
 *	\param *lcd Pointer to LCD display.
 *	\param year_var Value of displayed year.
 *	\param month_var Value of displayed month.
 *	\param day_var Value of displayed day.
 */

/*!
 *	\fn void cycleThroughSecond(void)
 *  \brief Function used to iterate date/time variables to increment device date and time based on CPU clocks.
 */

/*!
 *	\fn dateTime getDateTimeByKey(dateTimeKey key)
 *	\brief Function used to get dateTime value from dateTimeMap.
 *	\param key Enum key to find in map.
 *	\return dateTime Value of a key in the map.
 */

/*!
 *	\fn void setAll(uint16_t year_var, uint16_t month_var, uint16_t day_var, uint16_t hour_var, uint16_t minute_var, uint16_t second_var);
 *	\brief Function used to set values of all date/time variables in dateTimeMap.
 */

/*!
 *	\fn uint8_t getMaxDaysByMonth(monthsKey month_key)
 *	\brief Function used to get maximum number of days for checked month.
 *	\param month_key Index of month.
 *	\return uint8_t Maximum number of days value of inserted month.
 */

#include "lcd.h"

/************************************** Public enums **************************************/
typedef enum
{
	Second, //!< Representation of [0] index in dateTimeMap.
	Minute, //!< Representation of [1] index in dateTimeMap.
	Hour, //!< Representation of [2] index in dateTimeMap.
	Day, //!< Representation of [3] index in dateTimeMap.
	Month, //!< Representation of [4] index in dateTimeMap.
	Year //!< Representation of [5] index in dateTimeMap.
} dateTimeKey;

typedef enum
{
	Jan = 1, //!< Representation of January month with [1] index.
	Feb = 2, //!< Representation of February month with [2] index.
	Mar = 3, //!< Representation of March month with [3] index.
	Apr = 4, //!< Representation of April month with [4] index.
	May = 5, //!< Representation of May month with [5] index.
	Jun = 6, //!< Representation of June month with [6] index.
	Jul = 7, //!< Representation of July month with [7] index.
	Aug = 8, //!< Representation of August month with [8] index.
	Sep = 9, //!< Representation of September month with [9] index.
	Oct = 10, //!< Representation of October month with [10] index.
	Nov = 11, //!< Representation of November month with [11] index.
	Dec = 12 //!< Representation of December month with [12] index.
} monthsKey;

/************************************** Public structures **************************************/
typedef struct
{
	uint16_t currentValue; //!< Current value of date/time variable.
	uint16_t maxValue; //!< Maximum value of date/time variable.
	uint8_t minValue; //!< Minimum value of date/time variable.
} dateTime;

typedef struct
{
	uint16_t year; //!< Value of year in date.
	uint8_t month; //!< Value of month in date.
	uint8_t day; //!< Value of day in date.
	uint8_t hour; //!< Value of hour in date.
	uint8_t minute; //!< Value of minute in date.
	uint8_t second; //!< Value of second in date.
} dateUnit;

/************************************** Public function prototypes **************************************/
void Lcd_displayTime(Lcd_HandleTypeDef *lcd, uint8_t hour_var, uint8_t minute_var, uint8_t second_var);
void Lcd_displayDate(Lcd_HandleTypeDef *lcd, uint16_t year_var, uint8_t month_var, uint8_t day_var);
void cycleThroughSecond(void);
dateTime getDateTimeByKey(dateTimeKey key);
void setAll(uint16_t year_var, uint16_t month_var, uint16_t day_var, uint16_t hour_var, uint16_t minute_var, uint16_t second_var);
uint8_t getMaxDaysByMonth(monthsKey month_key);
