/*!
 *	\file main_screen.h
 * 	\brief This file contains public prototypes for displaying main screen.
 *
 *  \author Sigma
 */

/*!
 * 	\fn void mainScreenInit(Lcd_HandleTypeDef *lcd_var)
 * 	\brief Function used to initialize private variables for managing main screen.
 * 	\param *lcd_var Pointer to LCD display.
 */

/*!
 * 	\fn void displayMainScreen(void)
 * 	\brief Function used to display main screen.
 */

#include "lcd.h"

void mainScreenInit(Lcd_HandleTypeDef *lcd_var);
void displayMainScreen(void);
