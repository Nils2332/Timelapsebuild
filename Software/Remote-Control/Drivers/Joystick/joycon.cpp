/*
 * joycon.cpp
 *
 *  Created on: 22.02.2019
 *      Author: Nils
 */
#include "joycon.h"
#include "math.h"
#include "gpio.h"
#include "adc.h"

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

joycon::joycon(ADC_HandleTypeDef* hadc, uint32_t Channel0, uint32_t Channel1,
		GPIO_TypeDef* GPIOx, uint32_t Button)
{
	this->hadc = hadc;
	this->Channel0 = Channel0;
	this->Channel1 = Channel1;
}

void joycon::init()
{
	getjoycon();
	joyval_offset[0] = joyval[0];
	joyval_offset[1] = joyval[1];
}

void joycon::update()
{
	getjoycon();
	for(uint8_t i=0; i<2; i++)
	{
		joyval[i] = (joyval[i]-joyval_offset[i])/-10;

		if(abs(joyval[i])<8) joyval[i] = 0;

		if(joyval[i]>150) joyval[i] = 150;
		if(joyval[i]<-150) joyval[i] = -150;

		joyval[i] /=150;

	//	if(joyval[i] > 0 ) joyval[i]= sqrt(joyval[i]);
	//	if(joyval[i] < 0 ) joyval[i]= -sqrt(-joyval[i]);
	}
}

void joycon::getjoycon()
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = Channel0;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_ConfigChannel(hadc, &sConfig);

	getvals(0);

	sConfig.Channel = Channel1;
	HAL_ADC_ConfigChannel(hadc, &sConfig);

	getvals(1);
}

void joycon::getvals(uint8_t axis)
{
	joyval[axis] = 0;
	for(uint8_t j=0; j<mean; j++)
	{
		for(uint8_t i = 0; i < mid; i++) {
			HAL_ADC_Start(hadc);
			HAL_ADC_PollForConversion(hadc, 1);
			adc_buf[i] = HAL_ADC_GetValue(hadc);
			HAL_ADC_Stop(hadc);
		}
		qsort(adc_buf, mid, sizeof(uint16_t), compare);
		joyval[axis] += adc_buf[midpos];
	}
	joyval[axis] = (joyval[axis]/mean);
}


