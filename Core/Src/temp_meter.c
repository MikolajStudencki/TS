#include "temp_meter.h"

static void readTemperatureSensorVoltage(ADC_HandleTypeDef *hadc1);

static const uint16_t adc_range = 4095;
static const float adc_v_ref = 3.3;
static float adc_value;
static float adc_voltage;
static int8_t temperature;
static int8_t alarmTemperature = 36;

int8_t getCurrentTemperature(ADC_HandleTypeDef *hadc1)
{
	readTemperatureSensorVoltage(hadc1);
	temperature = 100 - (50 * adc_voltage);
	return temperature;
}

int8_t getAlarmTemperature()
{
	return alarmTemperature;
}

void setAlaramTemperature(int8_t alarmTemperature_var)
{
	alarmTemperature = alarmTemperature_var;
}

static void readTemperatureSensorVoltage(ADC_HandleTypeDef *hadc1)
{
	HAL_ADC_Start(hadc1);
	HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY);
	adc_value = HAL_ADC_GetValue(hadc1);
	adc_voltage = adc_value * (adc_v_ref / adc_range);
}
