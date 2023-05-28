#include "datetime.h"
#include "main.h"
#include "lcd.h"

typedef struct
{
	int8_t alarmTemperature;
	dateUnit alarmDate;
	uint32_t alarmDuration;
} temperatureHistory;

void tempMeterInit(Lcd_HandleTypeDef *lcd_var, ADC_HandleTypeDef *hadc1_var);
int8_t getCurrentTemperature(void);
void setAlarmTemperature(int8_t alarmTemperature_var);
int8_t getAlarmTemperature(void);
void setTurnOffAlarmTemperature(int8_t turnOff_alarmTemperature_var);
int8_t getTurnOffAlarmTemperature(void);
void displayTemperature(int8_t temp_var, uint8_t row_var, uint8_t col_var, char tempType);
void checkTemperatureState(void);
uint16_t getAlarmsCounter(void);
