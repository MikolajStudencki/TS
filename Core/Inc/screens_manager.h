#include "main.h"
#include "lcd.h"

void screensManagerInit(Lcd_HandleTypeDef *lcd_var, uint8_t *screen_index_var, uint8_t *last_screen_index_var);
void incrementDisplayIndex(void);
void decrementDisplayIndex(void);
void doNothing(void);
uint8_t getScreenIndex(void);
uint8_t getLastScreenIndex(void);
void setLastScreenIndex(void);

