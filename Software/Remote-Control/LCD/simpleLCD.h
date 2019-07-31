/*
 * simpleLCD.h
 *
 *  Created on: 29.07.2019
 *      Author: Nils
 */

#ifndef SIMPLELCD_H_
#define SIMPLELCD_H_

#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


void Lcd_Writ_Bus(unsigned char d);
void Lcd_Write_Com(unsigned char VH);
void Lcd_Write_Data(unsigned char VH);
void Lcd_Write_Com_Data(unsigned char com,unsigned char dat);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void Lcd_Init(void);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c);
void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c);
int RGB(int r,int g,int b);
void LCD_Clear(unsigned int j);


#ifdef __cplusplus
}
#endif

#endif /* SIMPLELCD_H_ */
