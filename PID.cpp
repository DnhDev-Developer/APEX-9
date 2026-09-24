#include "PID.h"

void PID_Init(
    PID *pid,
    float kp,
    float ki,
    float kd,
    float min,
    float max
)
{
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;

    pid->integral = 0;
    pid->previousError = 0;

    pid->outputMin = min;
    pid->outputMax = max;
}

float PID_Update(
    PID *pid,
    float setpoint,
    float measurement,
    float dt
)
{
    float error = setpoint - measurement;

    pid->integral += error * dt;

    float derivative =
        (error - pid->previousError) / dt;

    float output =
        pid->Kp * error +
        pid->Ki * pid->integral +
        pid->Kd * derivative;

    if (output > pid->outputMax)
        output = pid->outputMax;

    if (output < pid->outputMin)
        output = pid->outputMin;

    pid->previousError = error;

    return output;
}

void PID_Reset(PID *pid)
{
    pid->integral = 0;
    pid->previousError = 0;
}