#include "Battery.h"

extern ADC_HandleTypeDef hadc2;

#define ADC_MAX        4095.0f
#define ADC_VOLTAGE    3.3f

/*
 * Exemplo:
 *
 * R1 = 100k
 * R2 = 47k
 *
 * Vin máximo ≈ 10.3 V
 */

#define R1 100000.0f
#define R2 47000.0f

float Battery_GetVoltage(void)
{
    HAL_ADC_Start(&hadc2);

    HAL_ADC_PollForConversion(
        &hadc2,
        10
    );

    uint32_t adc =
        HAL_ADC_GetValue(&hadc2);

    HAL_ADC_Stop(&hadc2);

    float voltageADC =
        (adc / ADC_MAX) * ADC_VOLTAGE;

    float battery =
        voltageADC *
        ((R1 + R2) / R2);

    return battery;
}

bool Battery_Low(void)
{
    return Battery_GetVoltage() < 7.0f;
}