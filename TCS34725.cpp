#include "TCS34725.h"

extern I2C_HandleTypeDef hi2c1;

#define TCS34725_ADDR      (0x29 << 1)

#define COMMAND            0x80

#define ENABLE             0x00
#define ATIME              0x01

#define CONTROL            0x0F

#define CDATAL             0x14
#define RDATAL             0x16
#define GDATAL             0x18
#define BDATAL             0x1A

static bool writeRegister(uint8_t reg, uint8_t value)
{
    uint8_t data[2];

    data[0] = COMMAND | reg;
    data[1] = value;

    return HAL_I2C_Master_Transmit(
        &hi2c1,
        TCS34725_ADDR,
        data,
        2,
        100
    ) == HAL_OK;
}

static bool readRegisters(uint8_t reg, uint8_t *data, uint8_t length)
{
    uint8_t command = COMMAND | reg;

    if (HAL_I2C_Master_Transmit(
        &hi2c1,
        TCS34725_ADDR,
        &command,
        1,
        100
    ) != HAL_OK)
        return false;

    return HAL_I2C_Master_Receive(
        &hi2c1,
        TCS34725_ADDR,
        data,
        length,
        100
    ) == HAL_OK;
}

bool TCS34725_Init(void)
{
    uint8_t id;

    if (!readRegisters(0x12, &id, 1))
        return false;

    writeRegister(ATIME, 0xD5);

    writeRegister(CONTROL, 0x01);

    writeRegister(
        ENABLE,
        0x03
    );

    HAL_Delay(10);

    return true;
}

bool TCS34725_Read(TCS_Color *color)
{
    uint8_t data[8];

    if (!readRegisters(CDATAL, data, 8))
        return false;

    color->clear =
        data[1] << 8 |
        data[0];

    color->red =
        data[3] << 8 |
        data[2];

    color->green =
        data[5] << 8 |
        data[4];

    color->blue =
        data[7] << 8 |
        data[6];

    return true;
}