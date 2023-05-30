/*!
 *	\file history_screen.h
 * 	\brief This file contains public prototypes for displaying history screen.
 *
 *  \author Sigma
 */

/*!
 * 	\fn void historyScreenInit(Lcd_HandleTypeDef *lcd_var)
 * 	\brief Function used to initialize private variables for managing history screen.
 * 	\param *lcd_var Pointer to LCD display.
 */

/*!
 * 	\fn void displayHistoryScreen(void)
 * 	\brief Function used to display alarms details and clear history.
 */

#include "lcd.h"

/************************************** Public function prototypes **************************************/
void historyScreenInit(Lcd_HandleTypeDef *lcd_var);
void displayHistoryScreen(void);
