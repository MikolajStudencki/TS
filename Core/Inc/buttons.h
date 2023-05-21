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
 *	\fn void readAllButtonStates()
 *	\brief Function used to read states of all button pins.
 */

/*!
 * 	\typedef typedef struct button
 * 	\brief Type definition for a structure used for storing data about used buttons.
 */

/*!
 *	\fn GPIO_PinState getButtonStateByKey(buttonsKey key)
 *	\brief Function used to get state of checked button.
 *	\param key Int value of button.
 *	\return GPIO_PinState State of button pin.
 */

#include "stm32f4xx_hal.h"
#include "main.h"

/************************************** Public enums **************************************/
typedef enum
{
	BTN_UP,
	BTN_DOWN,
	BTN_LEFT,
	BTN_MID,
	BTN_RIGHT
} buttonsKey;

/************************************** Public structures **************************************/
typedef struct
{
	GPIO_PinState pinState; //!< State of pin assigned to button
	GPIO_TypeDef* GPIOx; //!< GPIOx assigned to button
	uint16_t GPIO_Pin; //!< GPIO_Pin assigned to button
} button;

/************************************** Public function prototypes **************************************/
void readAllButtonStates();
GPIO_PinState getButtonStateByKey(buttonsKey key);
