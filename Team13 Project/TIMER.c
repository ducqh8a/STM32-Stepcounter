#include "TIMER.h"
/* Init TIMER 2 with 1 TICK = 100us and counter to 5000 TICK = 500ms*/
void initTIMER(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  	TIM2->PSC = 7200 - 1;
 	TIM2->ARR = 5000 - 1;
  	TIM2->CR1 |= TIM_CR1_URS;
  	TIM2->DIER |= TIM_DIER_UIE;
}
