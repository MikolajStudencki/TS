#include "stm32f4xx_hal.h"
#include "main.h"
#include "lcd.h"
#include "lcd_characters.h"
#include "datetime.h"
#include "buttons.h"

void displayChangeDateTimeScreen(Lcd_HandleTypeDef *lcd);
uint8_t getIsUpdated();
void setIsUpdated(uint8_t is_updated_var);
