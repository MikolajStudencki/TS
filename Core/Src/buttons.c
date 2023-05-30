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

static void (*btn_up_fun)();
static void (*btn_down_fun)();
static void (*btn_left_fun)();
static void (*btn_mid_fun)();
static void (*btn_right_fun)();

static buttonsKey last_btn;
static GPIO_PinState last_btn_state;
/************************************** Public functions **************************************/
buttonsKey getPushedButton(void)
{
	for (int button_key = 0; button_key < 5; button_key++)
	{
		if (getButtonState(buttons[button_key]) == GPIO_PIN_RESET)
		{
			if (last_btn == button_key &&
				last_btn_state == GPIO_PIN_RESET)
			{
				break;
			}
			last_btn = button_key;
			last_btn_state = GPIO_PIN_RESET;
			return button_key;
		}
	}
	return 5;
}

void callFunctionByButtonPushed()
{
	switch (getPushedButton())
	{
		case BTN_UP:
			btn_up_fun();
			break;
		case BTN_DOWN:
			btn_down_fun();
			break;
		case BTN_LEFT:
			btn_left_fun();
			break;
		case BTN_MID:
			btn_mid_fun();
			break;
		case BTN_RIGHT:
			btn_right_fun();
			break;
		default:
			last_btn_state = getButtonState(buttons[last_btn]);
			break;
	}
}

void setBtnUpFun(void (*btn_up_fun_var)())
{
	btn_up_fun = btn_up_fun_var;
}

void setBtnDownFun(void (*btn_down_fun_var)())
{
	btn_down_fun = btn_down_fun_var;
}

void setBtnLeftFun(void (*btn_left_fun_var)())
{
	btn_left_fun = btn_left_fun_var;
}

void setBtnMidFun(void (*btn_mid_fun_var)())
{
	btn_mid_fun = btn_mid_fun_var;
}

void setBtnRightFun(void (*btn_right_fun_var)())
{
	btn_right_fun = btn_right_fun_var;
}

/************************************** Private functions **************************************/
static GPIO_PinState getButtonState(button button_var)
{
	return HAL_GPIO_ReadPin(button_var.GPIOx, button_var.GPIO_Pin);
}
