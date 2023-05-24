#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "delay.h"

#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "math.h"

#include "i2c.h"
#include "LCD_I2C.h"
#include "MPU_I2C.h"
#include "LED.h"
#include "Switch.h"
#include "TIMER.h"

uint16_t Accel_X_RAW = 0;
uint16_t Accel_Y_RAW = 0;
uint16_t Accel_Z_RAW = 0;

float vectorprevious;
float vector;
float totalvector;
int Steps = 0;
uint32_t Count = 0u;

#endif
