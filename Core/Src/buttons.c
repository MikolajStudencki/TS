/*!
 *	\file buttons.h
 * 	\brief This file contains public implementations of functions, private prototypes,
 * 	variables and function implementations for buttons operations.
 *
 *  \author Sigma
 */

/*!
 *	\fn static GPIO_PinState getButtonState(button button_var)
 *	\brief Function used to get current state of button pin.
 *	\param button_var Index of checked button.
 *	\return GPIO_PinState Current state of button.
 */

/*!
 *	\fn buttonsKey getPushedButton(void)
 *	\brief Function used to get currently pushed button.
 *	\return buttonsKey Currently pushed button.
 */

/*!
 * 	\var static button buttonMap[5]
 * 	\brief Array of button variables
 *
 * 	Map indexes: [0] button up, [1] button down, [2] button left, [3] button mid, [4] button right.
 */

/*!
 * 	\var static void (*btn_up_fun)()
 * 	\brief Pointer to a function assigned to button up click.
 */

/*!
 * 	\var static void (*btn_down_fun)()
 * 	\brief Pointer to a function assigned to button down click.
 */

/*!
 * 	\var static void (*btn_left_fun)()
 * 	\brief Pointer to a function assigned to button left click.
 */

/*!
 * 	\var static void (*btn_mid_fun)()
 * 	\brief Pointer to a function assigned to button mid click.
 */

/*!
 * 	\var static void (*btn_right_fun)()
 * 	\brief Pointer to a function assigned to button right click.
 */

/*!
 * 	\var static buttonsKey last_btn
 * 	\brief Contains information of last clicked button.
 *
 * 	This variable is needed to avoid reading same button few times without pause.
 */

/*!
 * 	\var static GPIO_PinState last_btn_state
 * 	\brief Contains information of state of last clicked button.
 *
 * 	This variable is needed to avoid reading same button few times without pause.
 */

#include "buttons.h"

/************************************** Private function prototypes **************************************/
static GPIO_PinState getButtonState(button button_var);
static buttonsKey getPushedButton(void);

/************************************** Private variables **************************************/
static button buttonMap[5] =
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
			last_btn_state = getButtonState(buttonMap[last_btn]);
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

static buttonsKey getPushedButton(void)
{
	for (int button_key = 0; button_key < 5; button_key++)
	{
		if (getButtonState(buttonMap[button_key]) == GPIO_PIN_RESET)
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
