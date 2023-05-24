#ifndef MPU_I2C_H
#define MPU_I2C_H

#include "stm32f10x.h"
#include "inttypes.h"
#include "i2c.h"
#include "delay.h"

#define MPU6050_ADDR          0xD0

#define SMPLRT_DIV_REG        0x19
#define GYRO_CONFIG_REG       0x1B
#define ACCEL_CONFIG_REG      0x1C
#define ACCEL_XOUT_H_REG      0x3B
#define TEMP_OUT_H_REG        0x41
#define GYRO_XOUT_H_REG       0x43
#define PWR_MGMT_1_REG        0x6B
#define WHO_AM_I_REG          0x75

void MPU_Write (uint8_t Address, uint8_t Reg, uint8_t Data);
void MPU_Read (uint8_t Address, uint8_t Reg, uint8_t *buffer, uint8_t size);
void MPU6050_Init (void);

#endif
