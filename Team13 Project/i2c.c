#include "i2c.h"


uint32_t I2C_Timeout;

GPIO_InitTypeDef GPIO_I2C_InitStruct;

void I2C1_InitPins(I2C_PinsPack_t pinspack);
void I2C2_InitPins(I2C_PinsPack_t pinspack);
/* Init I2Cx*/
void I2Cx_Init(I2C_TypeDef* I2Cx, I2C_PinsPack_t pinspack, uint32_t clockSpeed) {
	I2C_InitTypeDef I2C_InitStruct;
	
	/* Enable clock */
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;	
	/* Set default I2C GPIO	settings */
	GPIO_I2C_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;	
	GPIO_I2C_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
	if (I2Cx == I2C1) {
		
		/* Enable clock */
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;		
		/* Enable pins */
		I2C1_InitPins(pinspack);		
		/* Set values */
		I2C_InitStruct.I2C_ClockSpeed = clockSpeed;
		I2C_InitStruct.I2C_AcknowledgedAddress = I2C1_ACKNOWLEDGED_ADDRESS;
		I2C_InitStruct.I2C_Mode = I2C1_MODE;
		I2C_InitStruct.I2C_OwnAddress1 = I2C1_OWN_ADDRESS;
		I2C_InitStruct.I2C_Ack = I2C1_ACK;
		I2C_InitStruct.I2C_DutyCycle = I2C1_DUTY_CYCLE;
		
	} else if (I2Cx == I2C2) {
		
		/* Enable clock */
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
		/* Enable pins */
		I2C2_InitPins(pinspack);		
		/* Set values */
		I2C_InitStruct.I2C_ClockSpeed = clockSpeed;
		I2C_InitStruct.I2C_AcknowledgedAddress = I2C2_ACKNOWLEDGED_ADDRESS;
		I2C_InitStruct.I2C_Mode = I2C2_MODE;
		I2C_InitStruct.I2C_OwnAddress1 = I2C2_OWN_ADDRESS;
		I2C_InitStruct.I2C_Ack = I2C2_ACK;
		I2C_InitStruct.I2C_DutyCycle = I2C2_DUTY_CYCLE;
	} 
	
	/* Disable I2C first */
	I2C_Cmd(I2Cx, DISABLE);
	/* Initialize I2C */
	I2C_Init(I2Cx, &I2C_InitStruct);
	/* Enable I2C */
	I2C_Cmd(I2Cx, ENABLE);
}
/* Send Data to Device*/
void I2C_Write(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t data) {
	
	I2C_Start(I2Cx, address, I2C_Direction_Transmitter, 0);
	I2C_WriteData(I2Cx, reg);
	I2C_WriteData(I2Cx, data);
	I2C_Stop(I2Cx);
}
/* Read array Data from Deivice*/
int8_t I2C_ReadMulti(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	uint8_t i;
	I2C_Start(I2Cx, address, I2C_Direction_Transmitter, 0);
	I2C_WriteData(I2Cx, reg);
	I2C_Stop(I2Cx);
	I2C_Start(I2Cx, address, I2C_Direction_Receiver, 1);
	for (i = 0; i < count; i++) {
		if (i == (count - 1)) {
			//Last byte
			data[i] = I2C_ReadNack(I2Cx);
		} else {
			data[i] = I2C_ReadAck(I2Cx);
		}
	}
	return 0;
}
/* Start working with Device*/
int16_t I2C_Start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction, uint8_t ack) {
	I2C_GenerateSTART(I2Cx, ENABLE);
	
	I2C_Timeout = I2C_TIMEOUT;
	while (!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB) && I2C_Timeout) {
		if (--I2C_Timeout == 0x00) {
			return 1;
		}
	}

	if (ack) {
		I2C_AcknowledgeConfig(I2C1, ENABLE);
	}
	
	I2C_Send7bitAddress(I2Cx, address, direction);

	if (direction == I2C_Direction_Transmitter) {
		I2C_Timeout = I2C_TIMEOUT;
		while (!I2C_GetFlagStatus(I2Cx, I2C_FLAG_ADDR) && I2C_Timeout) {
			if (--I2C_Timeout == 0x00) {
				return 1;
			}
		}
	} else if (direction == I2C_Direction_Receiver) {
		I2C_Timeout = I2C_TIMEOUT;
		while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) && I2C_Timeout) {
			if (--I2C_Timeout == 0x00) {
				return 1;
			}
		}
	}
	I2Cx->SR2;
	
	return 0;
}
/* Write in the DR register the data to be sent */
void I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data) {
	I2C_Timeout = I2C_TIMEOUT;
	while (!I2C_GetFlagStatus(I2Cx, I2C_FLAG_TXE) && I2C_Timeout) {
		I2C_Timeout--;
	}
	I2C_SendData(I2Cx, data);
}
/* Read 1 byte Acknowledge from Device*/
uint8_t I2C_ReadAck(I2C_TypeDef* I2Cx) {
	uint8_t data;
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	
	I2C_Timeout = I2C_TIMEOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) && I2C_Timeout) {
		I2C_Timeout--;
	}

	data = I2C_ReceiveData(I2Cx);
	return data;
}
/* Read 1 byte Data NO Acknowledge from Device*/
uint8_t I2C_ReadNack(I2C_TypeDef* I2Cx) {
	uint8_t data;
	
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	
	I2C_GenerateSTOP(I2Cx, ENABLE);
	
	I2C_Timeout = I2C_TIMEOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) && I2C_Timeout) {
		I2C_Timeout--;
	}

	data = I2C_ReceiveData(I2Cx);
	return data;
}
/* Stop working with Device*/
uint8_t I2C_Stop(I2C_TypeDef* I2Cx) {	
	I2C_Timeout = I2C_TIMEOUT;
	while (((!I2C_GetFlagStatus(I2Cx, I2C_FLAG_TXE)) || (!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF))) && I2C_Timeout) {
		if (--I2C_Timeout == 0x00) {
			return 1;
		}
	}
	I2C_GenerateSTOP(I2Cx, ENABLE);
	
	return 0;
}
/* Init I2C1 Pin*/
void I2C1_InitPins(I2C_PinsPack_t pinspack) {
	if(pinspack == Pin_PB8PB9) {
		/* Enable clock */
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		GPIO_I2C_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_Init(GPIOB, &GPIO_I2C_InitStruct);
		GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
	}
}
/* Init I2C2 Pin*/
void I2C2_InitPins(I2C_PinsPack_t pinspack) {
	
	if (pinspack == Pin_PB10PB11) {
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		GPIO_I2C_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;		
		GPIO_Init(GPIOB, &GPIO_I2C_InitStruct);
	} 
}
