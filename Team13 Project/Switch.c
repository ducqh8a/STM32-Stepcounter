#include "Switch.h"
/* Init SWITCH Pin*/
void switch_init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRH &= ~(GPIO_CRH_MODE12); 				// Set pin SS to input  
  	GPIOA->CRH &= ~(GPIO_CRH_CNF12);   				// Clear bit 18 and 19 in register CRH
	GPIOA->CRH |= 2<<18;						// Set input type to pull-updown	
	GPIOA->ODR |= GPIO_ODR_ODR12; 					// Set input type to pull-up
	
	GPIOA->CRH &= ~(GPIO_CRH_MODE13); 				// Set pin reset to input   
  	GPIOA->CRH &= ~(GPIO_CRH_CNF13);				// Clear bit 22 and 23 in register CRH  
  	GPIOA->CRH |= 2<<22;						// Set input type to pull-updown	
	GPIOA->ODR |= GPIO_ODR_ODR13; 					// Set input type to pull-up
}
/* Get Input Value*/
uint8_t input(uint16_t GPIO_Pin) {
	uint8_t bitstatus = 0x00; 
	/* Check bit Pin in IDR Register, bit = 1 to Unpressed, bit = 0 to Pressed*/
  	if ((GPIOA->IDR & GPIO_Pin) != (uint32_t)Bit_RESET) {
    		bitstatus = (uint8_t)Bit_SET;  				//  Unpressed SW
 	}
  	else {
    		bitstatus = (uint8_t)Bit_RESET; 			// Pressed SW
  	}
  	return bitstatus;
}
