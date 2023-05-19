/*
 * buttons.c
 *
 *  Created on: 19/05/2023 г.
 *      Author: Danylo Skrahlenko
 */
#include "buttons.h"

static button buttons[5] =
{
		{
				.key = "UP",
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_UP_GPIO_Port,
				.GPIO_Pin = BTN_UP_Pin,
				.value = "U"
		},
		{
				.key = "DOWN",
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_DOWN_GPIO_Port,
				.GPIO_Pin = BTN_DOWN_Pin,
				.value = "D"
		},
		{
				.key = "LEFT",
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_LEFT_GPIO_Port,
				.GPIO_Pin = BTN_LEFT_Pin,
				.value = "L"
		},
		{
				.key = "MID",
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_MID_GPIO_Port,
				.GPIO_Pin = BTN_MID_Pin,
				.value = "M"
		},
		{
				.key = "RIGHT",
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_RIGHT_GPIO_Port,
				.GPIO_Pin = BTN_RIGHT_Pin,
				.value = "R"
		}
};

void readAllButtonStatuses()
{
	for (int i = 0; i < 5; i++)
	{
		readButtonStatus(&buttons[i]);
	}
}

void readButtonStatus(button *g_button)
{
	g_button->pinState = HAL_GPIO_ReadPin(g_button->GPIOx, g_button->GPIO_Pin);
}

void displayButtonValue(Lcd_HandleTypeDef *lcd)
{
	Lcd_cursor(lcd, 1, 5);
	for (int i = 0; i < 5; i++)
	{
		if (buttons[i].pinState == GPIO_PIN_RESET)
		{
			Lcd_string(lcd, buttons[i].value);
			break;
		}
	}
	Lcd_string(lcd, " ");
}

GPIO_PinState getPinStateByKey(char *key)
{
	for (int i = 0; i < 5; i++)
	{
		if (buttons[i].key == key)
		{
			return buttons[i].pinState;
		}
	}
	return GPIO_PIN_SET;
}
