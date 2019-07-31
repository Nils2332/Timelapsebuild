/*
 * joycon.h
 *
 *  Created on: 22.02.2019
 *      Author: Nils
 */

#ifndef JOYSTICK_JOYCON_H_
#define JOYSTICK_JOYCON_H_

#include "adc.h"
#include "gpio.h"

class joycon{
public:

	double joyval[2];

	double joyval_offset[2];

	bool button = 0;

	ADC_HandleTypeDef* hadc;

	uint32_t Channel0, Channel1;
	uint8_t mid = 5;
	uint16_t adc_buf[5];
	uint8_t midpos = 2;
	uint8_t mean = 1;



	joycon(ADC_HandleTypeDef* hadc, uint32_t Channel0, uint32_t Channel1,
			GPIO_TypeDef* GPIOx, uint32_t Button);

	void init();

	void update();

	void getjoycon();

	void getvals(uint8_t axis);


private:

};


#endif /* JOYSTICK_JOYCON_H_ */
