#include "main.h"

int main(void) {		 
	SysTick_Init();                         						// Init Systick Timer
	initLED();										// Init Led
	switch_init();										// Init Switch
  	initTIMER();										// Init Timer 2
	I2Cx_Init(I2C1, Pin_PB8PB9, 100000);    						// Init I2C1 with PB8(SCL) and PB9(SDA)   
	I2Cx_Init(I2C2, Pin_PB10PB11, 100000);							// Init I2C2 with PB10(SCL) and PB11(SDA)
	delay(100);
	MPU6050_Init ();									// Init Device MPU6050
	LCD_LiquidCrystal_I2C(0x4E, 16, 2);							// Init Device LCD16x2 
	LCD_backlight();									// Turn on the backlight
	LCD_clear();										// Clear display LCD
	char data[4];
	uint8_t buffer[6]={0,0,0,0,0,0};
	 
	while(1) {
 	  
		I2C_Write(I2C2,0xD0,0x1C,0x00);							// Write Data to MPU with Address 0x68 << 1 and register ACCEL_CONFIG 
		I2C_ReadMulti(I2C2,0xD0,0x3B,buffer,6);						// Read array Data from MPU with register ACCEL_XOUT_H 
		Accel_X_RAW = (int16_t)(buffer[0] << 8 | buffer [1]);			
		Accel_Y_RAW = (int16_t)(buffer[2] << 8 | buffer [3]);
		Accel_Z_RAW = (int16_t)(buffer[4] << 8 | buffer [5]);
		/* Pressed Reset Pin Switch*/
		if(0u == input(Pin_RESET)) {
			LCD_clear();								// Clear display LCD
			TIM2->CR1 &= ~TIM_CR1_CEN;						// Disable TIM2
			GPIOC->BRR |= GPIO_BRR_BR14;						// Turn off the BLUE led													
			GPIOC->BSRR |= GPIO_BSRR_BS15;						// Turn on the RED led
			Steps = 0;								// Reset counter step
			LCD_setCursor(1,0);							// Print string in column 2, row 1		 																
			LCD_printstr("HTDuc - NKKien");						// Print string 													
			LCD_setCursor(3,1);							// Print string in column 4, row 2
			LCD_printstr("Steps= ");						// Print string
			sprintf(data, "%d", Steps);						// Convert Steps from int to char
			LCD_printstr(data);							// Print Steps counter
		}
		/* Unpressed Reset Pin Switch*/
		else {
			GPIOC->BRR |= GPIO_BRR_BR15;						// Turn off the RED led
			/* Press Start Stop Pin Switch*/
			if(0u == input(Pin_SS)) {
				delay(100);							// Wait for some time to stabilize the system
				if(0u == input(Pin_SS)) {					// Check pressed SS Pin Switch again
					while(0u == input(Pin_SS));				// Wait to Unpressed SS Pin Switch
					Count++;						// Increase the counter by 1
				}	
			}
			/* If Count is odd*/
			if(Count % 2 !=0) {
				NVIC_EnableIRQ(TIM2_IRQn);					// Blink BLUE led with TIM2
				TIM2->CR1 |= TIM_CR1_CEN;					// Enable TIM2
				vector = sqrt( (Accel_X_RAW * Accel_X_RAW) + (Accel_Y_RAW * Accel_Y_RAW) + (Accel_Z_RAW * Accel_Z_RAW) ); // Calculate the Space Vector length
				totalvector = vector - vectorprevious;				// Calculate the difference from the previous value
				/* If totalvector > 6*/
				if (totalvector > 6){
					Steps++;						// Increase the Steps value by 1
				}
			}
			/* If Count is even*/
			else {
				TIM2->CR1 &= ~TIM_CR1_CEN;					// Disable TIM2		
				GPIOC->BRR |= GPIO_BRR_BR14;					// Turn off the BLUE led
			}
		}
		LCD_setCursor(1,0);								// Print string in column 2, row 1
		LCD_printstr("HTDuc - NKKien");							// Print string
		LCD_setCursor(3,1);								// Print string in column 4, row 2
		LCD_printstr("Steps= ");							// Print string
		sprintf(data, "%d", Steps);							// Convert Steps from int to char
		LCD_printstr(data);								// Print Steps counter
		vectorprevious = vector; 							// Save previous Space Vector length value
		delay(500);
	}
}
