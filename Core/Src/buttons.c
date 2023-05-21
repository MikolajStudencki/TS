/*!
 *	\file buttons.h
 * 	\brief This file contains public enums and prototypes for buttons operations.
 *
 *  Created 19/05/2023
 *  \author Danylo Skrahlenko
 */

/*!
 *	\fn static GPIO_PinState getButtonState(button button_var)
 *	\brief Function used to get current state of button pin.
 *	\param button_var Index of checked button.
 *	\return GPIO_PinState Current state of button.
 */

#include "buttons.h"

/************************************** Private function prototypes **************************************/
static GPIO_PinState getButtonState(button button_var);

/************************************** Private variables **************************************/
static button buttons[5] =
{
		{
				.GPIOx = BTN_UP_GPIO_Port,
				.GPIO_Pin = BTN_UP_Pin
		},
		{
				.GPIOx = BTN_DOWN_GPIO_Port,
				.GPIO_Pin = BTN_DOWN_Pin
		},
		{
				.GPIOx = BTN_LEFT_GPIO_Port,
				.GPIO_Pin = BTN_LEFT_Pin
		},
		{
				.GPIOx = BTN_MID_GPIO_Port,
				.GPIO_Pin = BTN_MID_Pin
		},
		{
				.GPIOx = BTN_RIGHT_GPIO_Port,
				.GPIO_Pin = BTN_RIGHT_Pin
		}
};

/************************************** Public functions **************************************/
buttonsKey getPushedButton(void)
{
	for (int button_key = 0; button_key < 5; button_key++)
	{
		if (getButtonState(buttons[button_key]) == GPIO_PIN_RESET)
		{
			return button_key;
		}
	}
	return 5;
}

/************************************** Private functions **************************************/
static GPIO_PinState getButtonState(button button_var)
{
	return HAL_GPIO_ReadPin(button_var.GPIOx, button_var.GPIO_Pin);
}
