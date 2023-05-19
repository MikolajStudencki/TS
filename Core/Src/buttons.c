/*
 * buttons.c
 *
 *  Created on: 19 мая 2023 г.
 *      Author: skrah
 */
#include "buttons.h"

void button_pressed(Lcd_HandleTypeDef lcd){
	Lcd_cursor(&lcd, 1, 5);
	int button_up = HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin);
	int button_down = HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin);
	int button_left = HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port, BTN_LEFT_Pin);
	int button_right = HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port, BTN_RIGHT_Pin);
	int button_mid = HAL_GPIO_ReadPin(BTN_MID_GPIO_Port, BTN_MID_Pin);
	if(button_up==0){
		Lcd_string(&lcd, "U");
	}
	if(button_down==0){
		Lcd_string(&lcd, "D");
	}
	if(button_left==0){
		Lcd_string(&lcd, "L");
	}
	if(button_right==0){
		Lcd_string(&lcd, "R");
	}
	if(button_mid==0){
		Lcd_string(&lcd, "M");
	}
}



