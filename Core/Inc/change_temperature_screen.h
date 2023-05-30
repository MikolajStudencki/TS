/*!
 *	\file change_temperature_screen.h
 * 	\brief This file contains public prototypes for displaying temperature screen.
 *
 *  \author Sigma
 */

/*!
 * 	\fn void changeTemperatureScreenInit(Lcd_HandleTypeDef *lcd_var)
 * 	\brief Function used to initialize private variables for managing temperature screen.
 * 	\param *lcd_var Pointer to LCD display.
 */

/*!
 * 	\fn void displayChangeTemperatureScreen(void)
 * 	\brief Function used to display and operate changing alarm and alarm turn off temperature.
 */

#include "lcd.h"

/************************************** Public function prototypes **************************************/
void changeTemperatureScreenInit(Lcd_HandleTypeDef *lcd_var);
void displayChangeTemperatureScreen(void);
