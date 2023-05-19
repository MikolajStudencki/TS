/*
 * buttons.h
 *
 *  Created on: 19 мая 2023 г.
 *      Author: skrah
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include "lcd.h"

typedef struct
{
	char *key;
	GPIO_PinState pinState;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	char *value;
} button;

void readAllButtonStatuses();
void readButtonStatus(button *g_button);
void displayButtonValue(Lcd_HandleTypeDef *lcd);
GPIO_PinState getPinStateByKey(char *key);
