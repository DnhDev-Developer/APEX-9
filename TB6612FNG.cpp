#include "TB6612FNG.h"

extern TIM_HandleTypeDef htim2;

#define LEFT_IN1_PORT   GPIOA
#define LEFT_IN1_PIN    GPIO_PIN_0

#define LEFT_IN2_PORT   GPIOA
#define LEFT_IN2_PIN    GPIO_PIN_1

#define RIGHT_IN1_PORT  GPIOA
#define RIGHT_IN1_PIN   GPIO_PIN_2

#define RIGHT_IN2_PORT  GPIOA
#define RIGHT_IN2_PIN   GPIO_PIN_3

#define STBY_PORT       GPIOA
#define STBY_PIN        GPIO_PIN_4

#define LEFT_PWM_CH     TIM_CHANNEL_1
#define RIGHT_PWM_CH    TIM_CHANNEL_2

static uint16_t pwmValue(int16_t speed)
{
    if (speed < 0)
        speed = -speed;

    if (speed > 1000)
        speed = 1000;

    return (uint16_t)((speed * __HAL_TIM_GET_AUTORELOAD(&htim2)) / 1000);
}

void TB6612_Init(void)
{
    HAL_GPIO_WritePin(STBY_PORT, STBY_PIN, GPIO_PIN_SET);

    HAL_TIM_PWM_Start(&htim2, LEFT_PWM_CH);
    HAL_TIM_PWM_Start(&htim2, RIGHT_PWM_CH);

    Motors_Stop();
}

void Motor_Left(int16_t speed)
{
    if (speed > 0)
    {
        HAL_GPIO_WritePin(LEFT_IN1_PORT, LEFT_IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LEFT_IN2_PORT, LEFT_IN2_PIN, GPIO_PIN_RESET);
    }
    else if (speed < 0)
    {
        HAL_GPIO_WritePin(LEFT_IN1_PORT, LEFT_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LEFT_IN2_PORT, LEFT_IN2_PIN, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LEFT_IN1_PORT, LEFT_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LEFT_IN2_PORT, LEFT_IN2_PIN, GPIO_PIN_RESET);
    }

    __HAL_TIM_SET_COMPARE(&htim2, LEFT_PWM_CH, pwmValue(speed));
}

void Motor_Right(int16_t speed)
{
    if (speed > 0)
    {
        HAL_GPIO_WritePin(RIGHT_IN1_PORT, RIGHT_IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RIGHT_IN2_PORT, RIGHT_IN2_PIN, GPIO_PIN_RESET);
    }
    else if (speed < 0)
    {
        HAL_GPIO_WritePin(RIGHT_IN1_PORT, RIGHT_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RIGHT_IN2_PORT, RIGHT_IN2_PIN, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(RIGHT_IN1_PORT, RIGHT_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RIGHT_IN2_PORT, RIGHT_IN2_PIN, GPIO_PIN_RESET);
    }

    __HAL_TIM_SET_COMPARE(&htim2, RIGHT_PWM_CH, pwmValue(speed));
}

void Motors_Stop(void)
{
    Motor_Left(0);
    Motor_Right(0);
}

void Motors_Brake(void)
{
    HAL_GPIO_WritePin(LEFT_IN1_PORT, LEFT_IN1_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LEFT_IN2_PORT, LEFT_IN2_PIN, GPIO_PIN_SET);

    HAL_GPIO_WritePin(RIGHT_IN1_PORT, RIGHT_IN1_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RIGHT_IN2_PORT, RIGHT_IN2_PIN, GPIO_PIN_SET);

    __HAL_TIM_SET_COMPARE(&htim2, LEFT_PWM_CH, 0);
    __HAL_TIM_SET_COMPARE(&htim2, RIGHT_PWM_CH, 0);
}