#ifndef __SWITCH_H
#define __SWITCH_H

#include "stm32f10x.h"

#define Pin_SS               		 ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define Pin_RESET                ((uint16_t)0x2000)  /*!< Pin 13 selected */

void switch_init(void);
uint8_t input(uint16_t GPIO_Pin);

#endif
