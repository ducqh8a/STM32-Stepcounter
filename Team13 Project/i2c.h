#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"

#ifndef I2C_TIMEOUT
#define I2C_TIMEOUT											20000
#endif

//I2C1 settings, change defines
#ifndef I2C1_ACKNOWLEDGED_ADDRESS
#define I2C1_ACKNOWLEDGED_ADDRESS				I2C_AcknowledgedAddress_7bit
#endif
#ifndef I2C1_MODE
#define I2C1_MODE												I2C_Mode_I2C
#endif
#ifndef I2C1_OWN_ADDRESS
#define I2C1_OWN_ADDRESS								0x00
#endif
#ifndef I2C1_ACK
#define I2C1_ACK												I2C_Ack_Disable
#endif
#ifndef I2C1_DUTY_CYCLE
#define I2C1_DUTY_CYCLE									I2C_DutyCycle_2
#endif

//I2C2 settings, change defines
#ifndef I2C2_ACKNOWLEDGED_ADDRESS
#define I2C2_ACKNOWLEDGED_ADDRESS				I2C_AcknowledgedAddress_7bit
#endif
#ifndef I2C2_MODE
#define I2C2_MODE												I2C_Mode_I2C
#endif
#ifndef I2C2_OWN_ADDRESS
#define I2C2_OWN_ADDRESS								0x00
#endif
#ifndef I2C2_ACK
#define I2C2_ACK												I2C_Ack_Disable
#endif
#ifndef I2C2_DUTY_CYCLE
#define I2C2_DUTY_CYCLE									I2C_DutyCycle_2
#endif

//I2C speed modes
#define I2C_CLOCK_STANDARD							100000
#define I2C_CLOCK_FAST_MODE							400000
#define I2C_CLOCK_FAST_MODE_PLUS				1000000
#define I2C_CLOCK_HIGH_SPEED						3400000

typedef enum {
	Pin_PB8PB9,
	Pin_PB10PB11,
} I2C_PinsPack_t;

extern void I2Cx_Init(I2C_TypeDef* I2Cx, I2C_PinsPack_t pinspack, uint32_t clockSpeed);
extern void I2C_Write(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t data);
extern int8_t I2C_ReadMulti(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);
extern int16_t I2C_Start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction, uint8_t ack);
extern uint8_t I2C_Stop(I2C_TypeDef* I2Cx);
extern uint8_t I2C_ReadNack(I2C_TypeDef* I2Cx);
extern uint8_t I2C_ReadAck(I2C_TypeDef* I2Cx);
extern void I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data);  

#endif
