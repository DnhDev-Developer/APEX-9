#include "QRE1113.h"

extern ADC_HandleTypeDef hadc1;

static uint16_t sensorMin[NUM_SENSORS];
static uint16_t sensorMax[NUM_SENSORS];

static uint16_t raw[NUM_SENSORS];

static const int16_t position[NUM_SENSORS] =
{
    -4000,
    -3000,
    -2000,
    -1000,
     0,
     1000,
     2000,
     3000,
     4000
};

void QRE_Init(void)
{
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        sensorMin[i] = 4095;
        sensorMax[i] = 0;
    }
}

void QRE_ReadRaw(uint16_t values[NUM_SENSORS])
{
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        HAL_ADC_Start(&hadc1);

        HAL_ADC_PollForConversion(&hadc1, 10);

        values[i] = HAL_ADC_GetValue(&hadc1);

        HAL_ADC_Stop(&hadc1);
    }
}

void QRE_Calibrate(void)
{
    uint16_t values[NUM_SENSORS];

    QRE_ReadRaw(values);

    for (int i = 0; i < NUM_SENSORS; i++)
    {
        if (values[i] < sensorMin[i])
            sensorMin[i] = values[i];

        if (values[i] > sensorMax[i])
            sensorMax[i] = values[i];
    }
}

float QRE_GetPosition(void)
{
    QRE_ReadRaw(raw);

    float numerator = 0;
    float denominator = 0;

    for (int i = 0; i < NUM_SENSORS; i++)
    {
        float value;

        if (sensorMax[i] == sensorMin[i])
            value = 0;
        else
            value =
                ((float)(raw[i] - sensorMin[i]) /
                (sensorMax[i] - sensorMin[i])) * 1000.0f;

        if (value < 0)
            value = 0;

        if (value > 1000)
            value = 1000;

        numerator += value * position[i];
        denominator += value;
    }

    if (denominator < 50)
        return 9999;

    return numerator / denominator;
}

bool QRE_LineDetected(void)
{
    float positionValue = QRE_GetPosition();

    return positionValue != 9999;
}