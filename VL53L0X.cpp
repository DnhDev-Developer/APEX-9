//vl53l0x_api.c
//vl53l0x_api.h
//vl53l0x_platform.c
//vl53l0x_platform.h
#include "VL53L0X.h"

#include "vl53l0x_api.h"

static VL53L0X_Dev_t device;

bool VL53L0X_Init(void)
{
    device.I2cDevAddr = 0x29;

    VL53L0X_WaitDeviceBooted(&device);

    VL53L0X_DataInit(&device);

    VL53L0X_StaticInit(&device);

    VL53L0X_PerformRefCalibration(
        &device,
        NULL,
        NULL
    );

    VL53L0X_PerformRefSpadManagement(
        &device,
        NULL,
        NULL
    );

    VL53L0X_SetDeviceMode(
        &device,
        VL53L0X_DEVICEMODE_SINGLE_RANGING
    );

    VL53L0X_StartMeasurement(&device);

    return true;
}

uint16_t VL53L0X_ReadDistance(void)
{
    VL53L0X_RangingMeasurementData_t measurement;

    VL53L0X_PerformSingleRangingMeasurement(
        &device,
        &measurement
    );

    return measurement.RangeMilliMeter;
}