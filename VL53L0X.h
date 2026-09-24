#ifndef VL53L0X_H
#define VL53L0X_H

#include "main.h"

bool VL53L0X_Init(void);

uint16_t VL53L0X_ReadDistance(void);

#endif