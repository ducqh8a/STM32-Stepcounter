#include "LED.h"
/* Init LED Pin*/
void initLED(void) {
	/* Enable clock */
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;			// Enable Port C Clock
	/* Init GPIO Pin*/
	GPIOC->CRH &= ~(GPIO_CRH_MODE14);  
  	GPIOC->CRH |= GPIO_CRH_MODE14; 				// Set output speed to high  
  	GPIOC->CRH &= ~(GPIO_CRH_CNF14); 			// Set output type to push-pull  
  	GPIOC->BRR |= GPIO_BRR_BR14; 				// Set output level to low 
	
	GPIOC->CRH &= ~(GPIO_CRH_MODE15);  
 	GPIOC->CRH |= GPIO_CRH_MODE15; 				// Set output speed to high  
  	GPIOC->CRH &= ~(GPIO_CRH_CNF15); 			// Set output type to push-pull  
 	GPIOC->BRR |= GPIO_BRR_BR15; 				// Set output level to low 
}
/* Blink LED SS with TIMER*/
void TIM2_IRQHandler(void) {
	/* Check Update interrupt Flag */
  	if ((TIM2->SR & TIM_SR_UIF) != 0) {
		 GPIOC->ODR ^= GPIO_ODR_ODR14;			// Blink Blue LED	
     		TIM2->SR &= ~TIM_SR_UIF;				// Reset bit 1 SR Register
  	}
}
