#ifndef ENCODER_H
#define ENCODER_H

#include "main.h"

void Encoder_Init(void);

int32_t Encoder_Left_Get(void);
int32_t Encoder_Right_Get(void);

void Encoder_Reset(void);

float Encoder_Left_RPM(void);
float Encoder_Right_RPM(void);

#endif