#include "Telemetry.h"

#include "stdio.h"

extern UART_HandleTypeDef huart1;

void Telemetry_Init(void)
{
}

void Telemetry_Send(
    float position,
    float leftRPM,
    float rightRPM,
    float battery
)
{
    char buffer[128];

    int length = snprintf(
        buffer,
        sizeof(buffer),
        "POS:%.2f,L:%.2f,R:%.2f,BAT:%.2f\r\n",
        position,
        leftRPM,
        rightRPM,
        battery
    );

    HAL_UART_Transmit(
        &huart1,
        (uint8_t*)buffer,
        length,
        100
    );
}