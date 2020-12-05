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
 
 *
 */
#include "HD44780.h"


//==========================================================================================
//
//==========================================================================================
void LCD_CHARACTERI::show (char *text , unsigned char line=255 ,unsigned char column=255)
{
	if(line!= 255 || column!=255)  GoTo(line,column);
	SendText(text);
}
//==========================================================================================
//
//==========================================================================================
void LCD_CHARACTERI::show (unsigned long character, unsigned char  line=255,unsigned char column=255)
{
	
	char buf[6];
	 if(line!= 255 || column!=255)  GoTo(line,column);
   
	
	
	
	if(character <= 9) LCD_SendData(character+48);
	
	else if(character <= 99 )
		{ 
		  buf[0] = character/10+48;
			buf[1] = character%10+48;
			show(buf,line,column);
		}
	
		else if(character <=999)
		{ 
		  buf[0] = character/100     +48;
			buf[1] = character/10%10   +48;
			buf[2] = character%10      +48;
			show(buf,line,column);
		}
		
		else if(character <=9999) //9216
		{ 
		  buf[0] = character/1000     +48;
			buf[1] = character/100%10   +48;
			buf[2] = character/10%10   +48;
			buf[3] = character%10      +48;
			show(buf,line,column);
		}
		else if(character <=99999) //9216
		{ 
		  buf[0] = character/10000     +48;
			buf[1] = character/1000%10   +48;
			buf[2] = character/100%10   +48;
			buf[3] = character/10%10   +48;
			buf[4] = character%10      +48;
			show(buf,line,column);
		}
				else if(character <=999999) //9216
		{ 
		  buf[0] = character/100000     +48;
			buf[1] = character/10000%10   +48;
			buf[2] = character/1000%10   +48;
			buf[3] = character/100%10   +48;
			buf[4] = character/10%10   +48;
			buf[5] = character%10      +48;
			show(buf,line,column);
		}
		else
		{
			show("sorry",line,column);
		}
 	

}
//==========================================================================================
//
//==========================================================================================
void LCD_CHARACTERI::delay_ms(int ms)
{
	long i, tms;
	tms = 9000*ms;
	for(i=0;i<tms;i++);
}

//==========================================================================================
//
//==========================================================================================

void LCD_CHARACTERI::delay_us(int us)
{
	long i, tus;
	tus = 9*us;
	for(i=0;i<tus;i++);
}

//==========================================================================================
//
//==========================================================================================

uint8_t LCD_CHARACTERI::LCD_ReadByte(void)
{

	 GPIO_InitTypeDef GPIO_InitStruct;
	uint8_t ReadedData=0;
	HAL_GPIO_WritePin(LCD_PORT, LCD_D_ALL,GPIO_PIN_SET);


GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
HAL_GPIO_Init(LCD_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(LCD_PORT, LCD_RW,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_SET);

	if(HAL_GPIO_ReadPin(LCD_PORT, LCD_D7))
		ReadedData |= 0x80;
	if(HAL_GPIO_ReadPin(LCD_PORT, LCD_D6))
		ReadedData |= 0x40;
	if(HAL_GPIO_ReadPin(LCD_PORT, LCD_D5))
		ReadedData |= 0x20;
	if(HAL_GPIO_ReadPin(LCD_PORT, LCD_D4))
		ReadedData |= 0x10;

	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_RESET);
	delay_us(50);
	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_SET);

	if(HAL_GPIO_ReadPin(LCD_PORT, LCD_D7))
		ReadedData |= 0x08;
	if(HAL_GPIO_ReadPin(LCD_PORT, LCD_D6))
		ReadedData |= 0x04;
	if(HAL_GPIO_ReadPin(LCD_PORT, LCD_D5))
		ReadedData |= 0x02;
	if(HAL_GPIO_ReadPin(LCD_PORT, LCD_D4))
		ReadedData |= 0x01;
	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_RESET);

GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
HAL_GPIO_Init(LCD_PORT, &GPIO_InitStruct);
	return ReadedData;
}

//==========================================================================================
//
//==========================================================================================

void LCD_CHARACTERI:: LCD_SendByte(uint8_t cmd)
{
	uint8_t tcmd = 0;

	HAL_GPIO_WritePin(LCD_PORT, LCD_RW,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_D_ALL,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_SET);

	tcmd = cmd >> 4;
	if( tcmd & 0x01 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D4,GPIO_PIN_SET);
	if( tcmd & 0x02 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D5,GPIO_PIN_SET);
	if( tcmd & 0x04 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D6,GPIO_PIN_SET);
	if( tcmd & 0x08 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D7,GPIO_PIN_SET);

	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_RESET);
	delay_us(50);
	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_D_ALL,GPIO_PIN_RESET);

	cmd &= 0x0F;
	if( cmd & 0x01 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D4,GPIO_PIN_SET);
	if( cmd & 0x02 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D5,GPIO_PIN_SET);
	if( cmd & 0x04 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D6,GPIO_PIN_SET);
	if( cmd & 0x08 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D7,GPIO_PIN_SET);

	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_D_ALL,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_RS,GPIO_PIN_RESET);
	while(LCD_ReadByte() & 0x80);
}

//==========================================================================================
//
//==========================================================================================

void LCD_CHARACTERI:: LCD_SendCmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_PORT, LCD_RS,GPIO_PIN_RESET);
	delay_us(50);
	LCD_SendByte(cmd);
}

//==========================================================================================
//
//==========================================================================================

void LCD_CHARACTERI:: LCD_SendData(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_PORT, LCD_RS,GPIO_PIN_SET);
	delay_us(50);
	LCD_SendByte(data);
}

//==========================================================================================
//   print a string on LCD.
//==========================================================================================

void LCD_CHARACTERI::SendText(char *text)
{
	while(*text)
	{
		LCD_SendData(*text);
		text++;
	}
}

//==========================================================================================
//   Clear the LCD display.
//==========================================================================================

void LCD_CHARACTERI::Clear(void)
{
	LCD_SendCmd(0x01);
}

//==========================================================================================
//   Set cursor position on LCD display.
//==========================================================================================

void LCD_CHARACTERI:: GoTo (unsigned char line, unsigned char column)
{
	uint8_t position = 0;

	position = (line * 0x40) + column;
	position = 0x80 + (position & 0x7F);

	LCD_SendCmd(position);
}

//==========================================================================================
//   Initialize the LCD.
//==========================================================================================

void LCD_CHARACTERI:: Init(void)
{
	uint8_t i;
	//char const *p;
	  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = (LCD_D7 | LCD_D6 | LCD_D5 | LCD_D4 | LCD_EN | LCD_RW | LCD_RS);
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_PORT, &GPIO_InitStruct);
	
	
	delay_ms(30);
	HAL_GPIO_WritePin(LCD_PORT, LCD_RS,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_RESET);
	for(i = 0; i<3; i++)
	{
		HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_PORT, LCD_D4 | LCD_D5,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_PORT, LCD_D6 | LCD_D7,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_RESET);
	}
	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_SET);
	delay_ms(50);
	HAL_GPIO_WritePin(LCD_PORT, LCD_D5,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_PORT,LCD_D4 | LCD_D6 | LCD_D7,GPIO_PIN_RESET);
	delay_ms(50);
	HAL_GPIO_WritePin(LCD_PORT, LCD_EN,GPIO_PIN_RESET);
	LCD_SendCmd(0x28);
	LCD_SendCmd(0x08);
	LCD_SendCmd(0x01);
	LCD_SendCmd(0x06);
	LCD_SendCmd(0x0C); //
	delay_ms(5);
    /* Load user-specific characters into CGRAM                               */
//	LCD_SendCmd(0x40);                  /* Set CGRAM address counter to 0     */
//	p = &UserFont[0][0];
//	for (i = 0; i < sizeof(UserFont); i++, p++)
//		LCD_SendData (*p);
//	LCD_SendCmd(0x80);                 /* Set DDRAM address counter to 0     */
}

