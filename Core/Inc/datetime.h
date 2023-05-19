/*!
 *	\file datetime.h
 * 	\brief This file contains public prototypes and structures for date-time.
 *
 *	This file contains public functions for getting, setting and displaying date and time
 *	on LCD display. It also contains structure type for date-time variables.
 *
 *  \created 19/05/2023
 *  \author Mikołaj Haglauer
 */

#include "lcd.h"

/************************************** Public structures **************************************/

/*!
 *	dataTime structure
 *
 *	This structure is used for managing dataTime variables that require
 *	having information about it's maximum and minimum values.
 */
typedef struct
{
	uint16_t currentValue; //!< variable storing current value.
	uint16_t maxValue; //!< variable storing maximum value.
	uint8_t minValue; //!< variable storing minimum value.
} dateTime;

/*!
 *	dt_Map structure
 *
 *	This structure is used for mapping dataTime variables with key values
 *	allowing to easily find needed variable and iterate through it.
 */
typedef struct
{
	char *key; //!< variable storing key value.
	dateTime dt_Var; //!< variable storing dateTime value.
} dt_Map;

/************************************** Public function prototypes **************************************/
/*!
 *	dateTimeInit function
 *
 *	This function is used to initialize private dateTime variables
 *	with default values.
 */
void dateTimeInit(void);

/*!
 *	cycleThroughSecond function
 *
 *	This function is used to iterate dateTime variables to increment
 *	device date and time based on CPU clocks.
 */
void cycleThroughSecond(void);

/*!
 *	displayTimeLcd function
 *
 *	This function is used to display device time on LCD. It takes
 *	6 spaces horizontally and 1 space vertically.
 *
 *	Template: hh-mm-ss
 *	\param lcd a Lcd_HandleTypeDef pointer to lcd.
 */
void displayTimeLcd(Lcd_HandleTypeDef *lcd);

/*!
 *	displayDateLcd function
 *
 *	This function is used to display device date on LCD. It takes
 *	8 spaces horizontally and 1 space vertically.
 *
 *	Template: YYYY-MM-DD
 *	\param lcd a Lcd_HandleTypeDef pointer to lcd.
 */
void displayDateLcd(Lcd_HandleTypeDef *lcd);

/*!
 *	setDate function
 *
 *	This function is used to set date of the device.
 *	\param s_year a uint16_t variable to set year.
 *	\param s_month a uint8_t variable to set month.
 *	\param s_day a uint8_t variable to set day.
 */
void setDate(uint16_t s_year, uint8_t s_month, uint8_t s_day);

/*!
 *	setTime function
 *
 *	This function is used to set time of the device.
 *	\param s_hour a uint16_t variable to set hour.
 *	\param s_minute a uint8_t variable to set minute.
 *	\param s_second a uint8_t variable to set second.
 */
void setTime(uint8_t s_hour, uint8_t s_minute, uint8_t s_second);

/*!
 *	getDateTimeByKey function
 *
 *	This function is used to get dateTime variable from device
 *	default dt_Map
 *
 *	\param key a char pointer to key string.
 */
dateTime *getDateTimeByKey(char *key);

