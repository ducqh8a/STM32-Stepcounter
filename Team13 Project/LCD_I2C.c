#include "LCD_I2C.h"

	uint8_t _addr;
	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;
	uint8_t _cols;
	uint8_t _rows;
	uint8_t _charsize;
	uint8_t _backlightval;
/* Init LCD I2C*/	
void LCD_LiquidCrystal_I2C(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows){
	_addr = lcd_addr;
	_cols = lcd_cols;
	_rows = lcd_rows;
	_backlightval = LCD_NOBACKLIGHT;
	LCD_begin();
}
/* Start LCD*/
void LCD_begin() {
	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

	if (_rows > 1) {
		_displayfunction |= LCD_2LINE;
	}

	if ((_charsize != 0) && (_rows == 1)) {
		_displayfunction |= LCD_5x10DOTS; 
	}

	delay(25);

	LCD_expanderWrite(_backlightval);
	delay(10);

	LCD_write4bits(0x03 << 4);
	delay(30); 

	// second try
	LCD_write4bits(0x03 << 4);
	delay(30); 

	// third go!
	LCD_write4bits(0x03 << 4);
	delay(10);

	LCD_write4bits(0x02 << 4);

	LCD_command(LCD_FUNCTIONSET | _displayfunction);

	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	LCD_display();

	LCD_clear();

	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	LCD_command(LCD_ENTRYMODESET | _displaymode);

	LCD_home();
}
/* Clear Display*/
void LCD_clear(){
	LCD_command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	delay(2000);  // this command takes a long time!
}
/* Set cursor position to zero*/
void LCD_home(){
	LCD_command(LCD_RETURNHOME);  // set cursor position to zero
	delay(2000);  // this command takes a long time!
}
/* Setting Cursor to print*/
void LCD_setCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if (row > _rows) {
		row = _rows-1; 
	}
	LCD_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}
/* No Display*/
void LCD_noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	LCD_command(LCD_DISPLAYCONTROL | _displaycontrol);
}
/* Display*/
void LCD_display() {
	_displaycontrol |= LCD_DISPLAYON;
	LCD_command(LCD_DISPLAYCONTROL | _displaycontrol);
}
/* Turn on the backlight*/
void LCD_backlight(void) {
	_backlightval=LCD_BACKLIGHT;
	LCD_expanderWrite(0);
}
/*Send command to LCD*/
void LCD_command(uint8_t value) {
	LCD_send(value, 0);
}
/* Write Data to LCD*/
void LCD_write(uint8_t value){
	LCD_send(value, Rs);
}
/* Send Data to LCD*/
void LCD_send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
	LCD_write4bits((highnib)|mode);
	LCD_write4bits((lownib)|mode);
}
/* Write 4bit Data to LCD*/
void LCD_write4bits(uint8_t value) {
	LCD_expanderWrite(value);
	LCD_pulseEnable(value);
}
/* Write array Data to LCD*/
void LCD_expanderWrite(uint8_t _data){
	I2C_Write(I2C1, _addr,0x00, (int)(_data) | _backlightval);
}
/* Enable pulse in LCD*/
void LCD_pulseEnable(uint8_t _data){
	LCD_expanderWrite(_data | En);
	delay(1);	

	LCD_expanderWrite(_data & ~En);
	delay(50);	
}
/* Print string in LCD*/
void LCD_printstr(const char *str){
	uint8_t i=0;
  while(str[i])
  {
    LCD_write(str[i]);
    i++;
  }
}
