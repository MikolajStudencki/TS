/*!
 *	\file buttons.h
 * 	\brief This file contains public enums, structs and prototypes for buttons operations.
 *
 *  \author Sigma
 */

/*!
 *	\typedef typedef enum buttonsKey
 *	\brief Type definition for an enum used for easier management of buttons.
 */

/*!
 * 	\typedef typedef struct button
 * 	\brief Type definition for a structure used for storing data about buttons.
 */

/*!
 *	\fn void callFunctionByButtonPushed(void)
 *	\brief Function used to call other functions depending on button pushed.
 */

/*!
 *	\fn void setBtnUpFun(void (*btn_up_fun_var)())
 *	\brief Function used to set BTN_UP function call.
 *	\param (*btn_up_fun_var)() Function set to this button.
 */

/*!
 *	\fn void setBtnDownFun(void (*btn_down_fun_var)())
 *	\brief Function used to set BTN_DOWN function call.
 *	\param (*btn_down_fun_var)() Function set to this button.
 */

/*!
 *	\fn void setBtnLeftFun(void (*btn_left_fun_var)())
 *	\brief Function used to set BTN_LEFT function call.
 *	\param (*btn_left_fun_var)() Function set to this button.
 */

/*!
 *	\fn void setBtnMidFun(void (*btn_mid_fun_var)())
 *	\brief Function used to set BTN_MID function call.
 *	\param (*btn_mid_fun_var)() Function set to this button.
 */

/*!
 *	\fn void setRightUpFun(void (*btn_right_fun_var)())
 *	\brief Function used to set BTN_RIGHT function call.
 *	\param (*btn_right_fun_var)() Function set to this button.
 */

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
void callFunctionByButtonPushed(void);
void setBtnUpFun(void (*btn_up_fun_var)());
void setBtnDownFun(void (*btn_down_fun_var)());
void setBtnLeftFun(void (*btn_left_fun_var)());
void setBtnMidFun(void (*btn_mid_fun_var)());
void setBtnRightFun(void (*btn_right_fun_var)());



