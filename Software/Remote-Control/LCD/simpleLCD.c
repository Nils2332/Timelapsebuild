/*
 * simpleLCD.c
 *
 *  Created on: 29.07.2019
 *      Author: Nils
 */
#include "gpio.h"

void Lcd_Writ_Bus(unsigned char d)
{

	/* Connection Rearrange if Pins not Syncron to port */
	uint8_t b0, b1, b2, b3, b4, b5, b6, b7;

	b0 = (d & 0b00000001) << 1;
	b1 = (d & 0b00000010) >> 1;
	b2 = (d & 0b00000100) << 5;
	b3 = (d & 0b00001000) << 3;
	b4 = (d & 0b00010000) << 1;
	b5 = (d & 0b00100000) >> 1;
	b6 = (d & 0b01000000) >> 3;
	b7 = (d & 0b10000000) >> 5;

	d = b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7;
	/*---------------------------------------*/

	HAL_GPIO_WritePin(GPIOB, d & 0x00FF, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, ~d & 0x00FF , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);
}


void Lcd_Write_Com(unsigned char VH)
{
	HAL_GPIO_WritePin(LCD_CD_GPIO_Port, LCD_CD_Pin, GPIO_PIN_RESET);//LCD_RS=0;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
	HAL_GPIO_WritePin(LCD_CD_GPIO_Port, LCD_CD_Pin, GPIO_PIN_SET);//LCD_RS=1;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com,unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
        Lcd_Write_Com(0x2a);
	Lcd_Write_Data(x1>>8);
	Lcd_Write_Data(x1);
	Lcd_Write_Data(x2>>8);
	Lcd_Write_Data(x2);
        Lcd_Write_Com(0x2b);
	Lcd_Write_Data(y1>>8);
	Lcd_Write_Data(y1);
	Lcd_Write_Data(y2>>8);
	Lcd_Write_Data(y2);
	Lcd_Write_Com(0x2c);
}

void Lcd_Init(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(5);
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(15);
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(15);

  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

    Lcd_Write_Com(0xF9);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x08);
    Lcd_Write_Com(0xC0);
    Lcd_Write_Data(0x19);
    Lcd_Write_Data(0x1A);
    Lcd_Write_Com(0xC1);
    Lcd_Write_Data(0x45);
    Lcd_Write_Data(0X00);
    Lcd_Write_Com(0xC2);
    Lcd_Write_Data(0x33);
    Lcd_Write_Com(0xC5);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x28);
    Lcd_Write_Com(0xB1);
    Lcd_Write_Data(0x90);
    Lcd_Write_Data(0x11);
    Lcd_Write_Com(0xB4);
    Lcd_Write_Data(0x02);
    Lcd_Write_Com(0xB6);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x42);
    Lcd_Write_Data(0x3B);
    Lcd_Write_Com(0xB7);
    Lcd_Write_Data(0x07);
    Lcd_Write_Com(0xE0);
    Lcd_Write_Data(0x1F);
    Lcd_Write_Data(0x25);
    Lcd_Write_Data(0x22);
    Lcd_Write_Data(0x0B);
    Lcd_Write_Data(0x06);
    Lcd_Write_Data(0x0A);
    Lcd_Write_Data(0x4E);
    Lcd_Write_Data(0xC6);
    Lcd_Write_Data(0x39);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Com(0xE1);
    Lcd_Write_Data(0x1F);
    Lcd_Write_Data(0x3F);
    Lcd_Write_Data(0x3F);
    Lcd_Write_Data(0x0F);
    Lcd_Write_Data(0x1F);
    Lcd_Write_Data(0x0F);
    Lcd_Write_Data(0x46);
    Lcd_Write_Data(0x49);
    Lcd_Write_Data(0x31);
    Lcd_Write_Data(0x05);
    Lcd_Write_Data(0x09);
    Lcd_Write_Data(0x03);
    Lcd_Write_Data(0x1C);
    Lcd_Write_Data(0x1A);
    Lcd_Write_Data(0x00);
    Lcd_Write_Com(0xF1);
    Lcd_Write_Data(0x36);
    Lcd_Write_Data(0x04);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x3C);
    Lcd_Write_Data(0x0F);
    Lcd_Write_Data(0x0F);
    Lcd_Write_Data(0xA4);
    Lcd_Write_Data(0x02);
    Lcd_Write_Com(0xF2);
    Lcd_Write_Data(0x18);
    Lcd_Write_Data(0xA3);
    Lcd_Write_Data(0x12);
    Lcd_Write_Data(0x02);
    Lcd_Write_Data(0x32);
    Lcd_Write_Data(0x12);
    Lcd_Write_Data(0xFF);
    Lcd_Write_Data(0x32);
    Lcd_Write_Data(0x00);
    Lcd_Write_Com(0xF4);
    Lcd_Write_Data(0x40);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x08);
    Lcd_Write_Data(0x91);
    Lcd_Write_Data(0x04);
    Lcd_Write_Com(0xF8);
    Lcd_Write_Data(0x21);
    Lcd_Write_Data(0x04);
    Lcd_Write_Com(0x36);
    Lcd_Write_Data(0x48);
    Lcd_Write_Com(0x3A);
    Lcd_Write_Data(0x55);

    Lcd_Write_Com(0x11);    //Exit Sleep
    HAL_Delay(120);
    Lcd_Write_Com(0x29);    //Display on
}

void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
{
  unsigned int i,j;
  Lcd_Write_Com(0x02c); //write_memory_start
  HAL_GPIO_WritePin(LCD_CD_GPIO_Port, LCD_CD_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
  l=l+x;
  Address_set(x,y,l,y);
  j=l*2;
  for(i=1;i<=j;i++)
  {
    Lcd_Write_Data(c);
  }
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
{
  unsigned int i,j;
  Lcd_Write_Com(0x02c); //write_memory_start
  HAL_GPIO_WritePin(LCD_CD_GPIO_Port, LCD_CD_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
  l=l+y;
  Address_set(x,y,x,l);
  j=l*2;
  for(i=1;i<=j;i++)
  {
    Lcd_Write_Data(c);
  }
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}

void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  unsigned int i;
  for(i=0;i<h;i++)
  {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}
int RGB(int r,int g,int b)
{return r << 16 | g << 8 | b;
}
void LCD_Clear(unsigned int j)
{
  unsigned int i,m;
 Address_set(0,0,320,480);
  //Lcd_Write_Com(0x02c); //write_memory_start
  //digitalWrite(LCD_RS,HIGH);
 HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);


  for(i=0;i<320;i++)
    for(m=0;m<480;m++)
    {
      Lcd_Write_Data(j>>8);
      Lcd_Write_Data(j);

    }
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}
