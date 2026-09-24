#ifndef PID_H
#define PID_H

typedef struct
{
    float Kp;
    float Ki;
    float Kd;

    float integral;
    float previousError;

    float outputMin;
    float outputMax;

} PID;

void PID_Init(
    PID *pid,
    float kp,
    float ki,
    float kd,
    float min,
    float max
);

float PID_Update(
    PID *pid,
    float setpoint,
    float measurement,
    float dt
);

void PID_Reset(PID *pid);

#endif