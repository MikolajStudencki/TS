/*!
 *	\file buttons.h
 * 	\brief This file contains public enums and prototypes for buttons operations.
 *
 *  Created 19/05/2023
 *  \author Danylo Skrahlenko
 */

/*!
 *	\typedef typedef enum buttonsKey
 *	\brief Type definition for an enum used for easier management of buttons.
 */

/*!
 * 	\typedef typedef struct button
 * 	\brief Type definition for a structure used for storing data about used buttons.
 */

/*!
 *	\fn buttonsKey getPushedButton(void)
 *	\brief Function used to get currently pushed button.
 *	\return buttonsKey Currently pushed button.
 */

/*!
 *	\fnvoid callFunctionByButtonPushed(void (*btn_up_fun_var)(), void (*btn_down_fun_var)(), void (*btn_left_fun_var)(), void (*btn_mid_fun_var)(), void (*btn_right_fun_var)())
 *	\brief Function used to call method depending on button pushed.
 *	\param btn_up_fun_var Pointer to function called if BTN_UP pushed.
 *	\param btn_down_fun_var Pointer to function called if BTN_DOWN pushed.
 *	\param btn_left_fun_var Pointer to function called if BTN_LEFT pushed.
 *	\param btn_mid_fun_var Pointer to function called if BTN_MID pushed.
 *	\param btn_right_fun_var Pointer to function called if BTN_RIGHT pushed.
 */

#include "stm32f4xx_hal.h"
#include "main.h"

/************************************** Public enums **************************************/
typedef enum
{
	BTN_UP, //!< Representation of [0] index in buttons.
	BTN_DOWN, //!< Representation of [1] index in buttons.
	BTN_LEFT, //!< Representation of [2] index in buttons.
	BTN_MID, //!< Representation of [3] index in buttons.
	BTN_RIGHT //!< Representation of [4] index in buttons.
} buttonsKey;

/************************************** Public structures **************************************/
typedef struct
{
	GPIO_PinState pinState; //!< State of pin assigned to button
	GPIO_TypeDef* GPIOx; //!< GPIOx assigned to button
	uint16_t GPIO_Pin; //!< GPIO_Pin assigned to button
} button;

/************************************** Public function prototypes **************************************/
buttonsKey getPushedButton(void);
void callFunctionByButtonPushed(void);
void set_btn_up_fun(void (*btn_up_fun_var)());
void set_btn_down_fun(void (*btn_down_fun_var)());
void set_btn_left_fun(void (*btn_left_fun_var)());
void set_btn_mid_fun(void (*btn_mid_fun_var)());
void set_btn_right_fun(void (*btn_right_fun_var)());



