#ifndef TB6612FNG_H
#define TB6612FNG_H

#include "main.h"

void TB6612_Init(void);

void Motor_Left(int16_t speed);
void Motor_Right(int16_t speed);

void Motors_Stop(void);
void Motors_Brake(void);

#endif