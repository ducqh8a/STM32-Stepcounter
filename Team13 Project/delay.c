#include "delay.h"

volatile uint32_t usTicks;
/* Init Systick to 1 TICK = 1 microsecond*/
void SysTick_Init(void) {
	
  	SysTick->LOAD = SystemCoreClock / 1000000; //Configured the SysTick to count in 1us
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_TICKINT_Msk |SysTick_CTRL_ENABLE_Msk; //Select Core Clock & Enable SysTick & Enable Interrupt
}
/* Function Delay microsecond*/
void delay (uint32_t TICK) { 
	while (usTicks < TICK);
	usTicks = 0; //Reset
}
/* Increase the counter by 1*/
void SysTick_Handler(void) {
  	usTicks++;
}
