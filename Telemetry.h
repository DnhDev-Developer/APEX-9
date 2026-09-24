#ifndef TELEMETRY_H
#define TELEMETRY_H

void Telemetry_Init(void);

void Telemetry_Send(
    float position,
    float leftRPM,
    float rightRPM,
    float battery
);

#endif