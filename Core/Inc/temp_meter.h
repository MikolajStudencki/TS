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
void Lcd_displayTemperature(Lcd_HandleTypeDef *lcd_var, int8_t temp_var, char tempType);
void checkTemperatureState(void);
void clearCounterHistory(void);
uint16_t getAlarmsCounter(void);
temperatureHistory *getTemperatureHistory(void);
