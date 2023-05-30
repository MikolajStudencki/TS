/*!
 *	\fn void changeDateTimeScreenInit(Lcd_HandleTypeDef *lcd_var)
 *	\brief Initializes the change date and time screen.
 *	\param lcd_var Pointer to the LCD handle structure.
 */

/*!
 *	\fn void displayChangeDateTimeScreen(void)
 *	\brief Displays the change date and time screen.
 */

/*!
 *	\fn void setIsUpdated(uint8_t is_updated_var)
 *	\brief Sets the update status of the screen.
 *	\param is_updated_var Update status variable.
 */
#include "lcd.h"

void changeDateTimeScreenInit(Lcd_HandleTypeDef *lcd_var);
void displayChangeDateTimeScreen(void);
void setIsUpdated(uint8_t is_updated_var);
