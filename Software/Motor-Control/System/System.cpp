#include "System.h"
#include <cstdarg>
#include <stdio.h>
#include <stdarg.h>

#include "gpio.h"
#include "usart.h"

#include "nRF905.h"
#include "adc.h"




namespace System {

	void analogRead(uint32_t channel, ADC_HandleTypeDef* ADC_handle, uint16_t *adc_data, uint8_t samples)
	{
		ADC_ChannelConfTypeDef sConfig = {0};
		sConfig.Channel = channel;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
		HAL_ADC_ConfigChannel(ADC_handle, &sConfig);
		for(int i = 0; i < samples; i++) {
			HAL_ADC_Start(ADC_handle);
			HAL_ADC_PollForConversion(ADC_handle, 1);
			adc_data[i] = HAL_ADC_GetValue(ADC_handle);
			HAL_ADC_Stop(ADC_handle);
		}
	}

	void print(const char *fmt, ...)
	{
	//#if DEBUG
	#ifndef NDEBUG
		char buffer[100];

		va_list arp;
		va_start(arp, fmt);
		uint16_t length = vsnprintf(buffer, sizeof(buffer), fmt, arp);
		va_end(arp);

		HAL_UART_Transmit(&huart1, (uint8_t*) buffer, length, 1000);
	#endif
	//#endif
	}

}
