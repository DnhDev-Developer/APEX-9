#include "Encoder.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

#define ENCODER_CPR  12.0f
#define GEAR_RATIO   30.0f

static int32_t leftTotal = 0;
static int32_t rightTotal = 0;

static int16_t leftLast = 0;
static int16_t rightLast = 0;

void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

    Encoder_Reset();
}

void Encoder_Reset(void)
{
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    __HAL_TIM_SET_COUNTER(&htim4, 0);

    leftTotal = 0;
    rightTotal = 0;

    leftLast = 0;
    rightLast = 0;
}

int32_t Encoder_Left_Get(void)
{
    int16_t current = (int16_t)__HAL_TIM_GET_COUNTER(&htim3);

    int16_t delta = current - leftLast;

    leftTotal += delta;
    leftLast = current;

    return leftTotal;
}

int32_t Encoder_Right_Get(void)
{
    int16_t current = (int16_t)__HAL_TIM_GET_COUNTER(&htim4);

    int16_t delta = current - rightLast;

    rightTotal += delta;
    rightLast = current;

    return rightTotal;
}

float Encoder_Left_RPM(void)
{
    static int32_t lastTicks = 0;

    int32_t ticks = Encoder_Left_Get();
    int32_t delta = ticks - lastTicks;

    lastTicks = ticks;

    return (delta / (ENCODER_CPR * GEAR_RATIO)) * 600.0f;
}

float Encoder_Right_RPM(void)
{
    static int32_t lastTicks = 0;

    int32_t ticks = Encoder_Right_Get();
    int32_t delta = ticks - lastTicks;

    lastTicks = ticks;

    return (delta / (ENCODER_CPR * GEAR_RATIO)) * 600.0f;
}