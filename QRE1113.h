#ifndef QRE1113_H
#define QRE1113_H

#include "main.h"

#define NUM_SENSORS 9

void QRE_Init(void);

void QRE_ReadRaw(uint16_t values[NUM_SENSORS]);

void QRE_Calibrate(void);

float QRE_GetPosition(void);

bool QRE_LineDetected(void);

#endif