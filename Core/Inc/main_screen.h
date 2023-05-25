/*!
 *	\file mainscreen.h
 * 	\brief This file contains public enums and prototypes for buttons operations.
 *
 *  Created 23/05/2023
 *  \author Mikołaj Haglauer
 */

#include "lcd.h"
#include "datetime.h"
#include "temp_meter.h"

void displayMainScreen(Lcd_HandleTypeDef *lcd, ADC_HandleTypeDef *hadc1);
