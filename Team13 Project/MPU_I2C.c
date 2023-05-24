#include "MPU_I2C.h"

int16_t check;
uint8_t Data;
/* Write Data to MPU*/
void MPU_Write (uint8_t Address, uint8_t Reg, uint8_t Data) {
	I2C_Write(I2C2, Address, Reg, Data);
}
/* Read Data from MPU*/
void MPU_Read (uint8_t Address, uint8_t Reg, uint8_t *buffer, uint8_t size) {
	I2C_ReadMulti(I2C2, Address, Reg, buffer, size);
}
/* Init MPU*/
void MPU6050_Init (void) {
	uint8_t check;
	uint8_t Data;

	// check device ID WHO_AM_I

	MPU_Read (MPU6050_ADDR,WHO_AM_I_REG, &check, 1);

	if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		MPU_Write (MPU6050_ADDR, PWR_MGMT_1_REG, Data);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		MPU_Write(MPU6050_ADDR, SMPLRT_DIV_REG, Data);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ? 2g
		Data = 0x00;
		MPU_Write(MPU6050_ADDR, ACCEL_CONFIG_REG, Data);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ? 250 ?/s
		Data = 0x00;
		MPU_Write(MPU6050_ADDR, GYRO_CONFIG_REG, Data);
	}

}
