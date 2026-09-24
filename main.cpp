#include "main.h"

#include "TB6612FNG.h"
#include "Encoder.h"
#include "QRE1113.h"
#include "TCS34725.h"
#include "VL53L0X.h"
#include "LineFollower.h"
#include "Battery.h"
#include "Telemetry.h"

void System_Init(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_ADC2_Init();

    MX_I2C1_Init();

    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();

    MX_USART1_UART_Init();

    TB6612_Init();

    Encoder_Init();

    QRE_Init();

    TCS34725_Init();

    VL53L0X_Init();

    LineFollower_Init();

    Telemetry_Init();
}

int main(void)
{
    System_Init();

    HAL_Delay(1000);

    uint32_t lastControl = HAL_GetTick();
    uint32_t lastTelemetry = HAL_GetTick();

    while (1)
    {
        uint32_t now = HAL_GetTick();

        /*
         * Loop de controle:
         * 1 ms
         */
        if (now - lastControl >= 1)
        {
            lastControl = now;

            LineFollower_Update(0.001f);
        }

        /*
         * Telemetria:
         * 50 Hz
         */
        if (now - lastTelemetry >= 20)
        {
            lastTelemetry = now;

            float position =
                QRE_GetPosition();

            float leftRPM =
                Encoder_Left_RPM();

            float rightRPM =
                Encoder_Right_RPM();

            float battery =
                Battery_GetVoltage();

            Telemetry_Send(
                position,
                leftRPM,
                rightRPM,
                battery
            );
        }

        /*
         * Proteção de bateria
         */
        if (Battery_Low())
        {
            Motors_Stop();
        }
    }
}