/*
 *
 *		LCD library for STM32F373cct6 processor.
 * 		LCDs use the HD44780 controller.
 *      Source code was modified and ported for working on True Studio.
 *      Modifier: mahdi8866
 *      Date: 13 Octobr 2016
 *      Web site: http://www.eca.ir
 *		e-mail:   mahdi110hoo110@yahoo.com
 *

 */
 
/* Connections between LCD and STM32F373cct6  */
#define LCD_RS          GPIO_PIN_1
#define LCD_RW          GPIO_PIN_2
#define LCD_EN          GPIO_PIN_3
#define LCD_D4          GPIO_PIN_4
#define LCD_D5          GPIO_PIN_5
#define LCD_D6			    GPIO_PIN_6
#define LCD_D7          GPIO_PIN_7
#define LCD_PORT        GPIOA        



#define LCD_D_ALL		   (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)


const char UserFont[8][8] = {  /* 8 user defined characters to be loaded into CGRAM (used for bargraph)*/
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10 },
    { 0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18 },
    { 0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C },
    { 0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E },
    { 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F },
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

class LCD_CHARACTERI{
	public:
 	void SendText(char *text);
  void GoTo (unsigned char line, unsigned char column);
  void Clear (void);
  void Init (void);
	void show (char *text , unsigned char line ,unsigned char column);
	void show (unsigned long , unsigned char  ,unsigned char );
	
  
 
  
	
	private:
	void delay_ms(int ms);
	void delay_us(int us);
	unsigned char LCD_ReadByte(void);
	void LCD_SendByte(unsigned char cmd);
  void LCD_SendCmd (unsigned char cmd);
  void LCD_SendData(unsigned char data);
}lcd;




 




