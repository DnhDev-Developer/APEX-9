#include "LineFollower.h"

#include "QRE1113.h"
#include "TB6612FNG.h"
#include "PID.h"

static PID linePID;

static float lastPosition = 0;

void LineFollower_Init(void)
{
    PID_Init(
        &linePID,

        0.08f,     // Kp
        0.0f,      // Ki
        0.12f,     // Kd

        -600,
        600
    );
}

void LineFollower_Update(float dt)
{
    float position = QRE_GetPosition();

    if (position == 9999)
    {
        /*
         * Linha perdida.
         * Continua procurando para o lado
         * onde a linha estava.
         */

        if (lastPosition > 0)
        {
            Motor_Left(-300);
            Motor_Right(500);
        }
        else
        {
            Motor_Left(500);
            Motor_Right(-300);
        }

        return;
    }

    lastPosition = position;

    float correction =
        PID_Update(
            &linePID,
            0,
            position,
            dt
        );

    int16_t baseSpeed = 650;

    int16_t left =
        baseSpeed + correction;

    int16_t right =
        baseSpeed - correction;

    if (left > 1000)
        left = 1000;

    if (left < -1000)
        left = -1000;

    if (right > 1000)
        right = 1000;

    if (right < -1000)
        right = -1000;

    Motor_Left(left);
    Motor_Right(right);
}