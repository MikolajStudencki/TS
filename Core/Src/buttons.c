/*!
 *	\file buttons.h
 * 	\brief This file contains public enums and prototypes for buttons operations.
 *
 *  Created 19/05/2023
 *  \author Danylo Skrahlenko
 */

/*!
 *	\fn static void readButtonState(button *button_var)
 *	\brief Function used to read current state of button pin.
 *	\param button_var Pointer to checked button.
 */

#include "buttons.h"

/************************************** Private function prototypes **************************************/
static void readButtonState(button *button_var);

/************************************** Private variables **************************************/
static button buttons[5] =
{
		{
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_UP_GPIO_Port,
				.GPIO_Pin = BTN_UP_Pin
		},
		{
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_DOWN_GPIO_Port,
				.GPIO_Pin = BTN_DOWN_Pin
		},
		{
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_LEFT_GPIO_Port,
				.GPIO_Pin = BTN_LEFT_Pin
		},
		{
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_MID_GPIO_Port,
				.GPIO_Pin = BTN_MID_Pin
		},
		{
				.pinState = GPIO_PIN_SET,
				.GPIOx = BTN_RIGHT_GPIO_Port,
				.GPIO_Pin = BTN_RIGHT_Pin
		}
};

/************************************** Public functions **************************************/
void readAllButtonStates()
{
	for (int i = 0; i < 5; i++)
	{
		readButtonState(&buttons[i]);
	}
}

GPIO_PinState getButtonStateByKey(buttonsKey key)
{
	return buttons[key].pinState;
}

/************************************** Private functions **************************************/
static void readButtonState(button *button_var)
{
	button_var->pinState = HAL_GPIO_ReadPin(button_var->GPIOx, button_var->GPIO_Pin);
}
