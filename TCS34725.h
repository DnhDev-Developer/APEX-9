#ifndef TCS34725_H
#define TCS34725_H

#include "main.h"

typedef struct
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t clear;
} TCS_Color;

bool TCS34725_Init(void);

bool TCS34725_Read(TCS_Color *color);

#endif