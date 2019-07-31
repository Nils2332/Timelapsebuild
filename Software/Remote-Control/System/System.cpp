#include "System.h"
#include <cstdarg>
#include <stdio.h>
#include <stdarg.h>

#include "gpio.h"
#include "usart.h"

#include "nRF905.h"

#define RXADDR2 0xFE1337AC
#define TXADDR2 0xFE1337AD // Address of device to send to

uint8_t rxdata2[10] = {0};
uint8_t txdata2[10] = {0};

namespace System {

	void sendcheck(uint8_t *pData, uint8_t len)
	{
		bool datasend = 0;
		uint8_t maxcounter = 5;
		uint8_t counter = 0;

		for(int i=0; i<10; i++)
			txdata2[i] = 0;

		for(int i=0 ; i<len; i++)
			txdata2[i] = pData[i];

		uint8_t checksum = 0;

		for(int i=0; i<9; i++){
			checksum += txdata2[i];
		}

		txdata2[9] = checksum;

		while(!datasend && counter <maxcounter)
		{
			while(HAL_GPIO_ReadPin(RF_CD_GPIO_Port, RF_CD_Pin));

			nRF905_TX(TXADDR2, txdata2, 10, NRF905_NEXTMODE_RX);

			uint16_t timecounter = 0;
			while(!dataReady() && timecounter < 50){
				timecounter++;
				HAL_Delay(1);
			}

			if(dataReady()){
				nRF905_read(rxdata2, 10);

				if(rxdata2[0] == 200 && rxdata2[8] == 0xAA){
					datasend = 1;
				}
			}

			counter++;
		}
	}

	void sendrecieve(uint8_t *pDatain, uint8_t len_i, uint8_t *pDataout, uint8_t len_o)
	{
		bool datasend = 0;
		uint8_t maxcounter = 5;
		uint8_t counter = 0;

		for(int i=0; i<10; i++)
			txdata2[i] = 0;

		for(int i=0 ; i<len_i; i++)
			txdata2[i] = pDatain[i];

		uint8_t checksum = 0;

		for(int i=0; i<9; i++){
			checksum += txdata2[i];
		}

		txdata2[9] = checksum;

		while(!datasend && counter <maxcounter)
		{
			while(HAL_GPIO_ReadPin(RF_CD_GPIO_Port, RF_CD_Pin));

			nRF905_TX(TXADDR2, txdata2, 10, NRF905_NEXTMODE_RX);

			uint16_t timecounter = 0;
			while(!dataReady() && timecounter < 50){
				timecounter++;
				HAL_Delay(1);
			}

			if(dataReady()){
				nRF905_read(rxdata2, 10);

				checksum = 0;
				for(int i=0; i<9; i++){
					checksum += rxdata2[i];
				}

				if(checksum == rxdata2[9]){
					datasend = 1;
					for(uint8_t i = 0; i<len_o; i++){
						pDataout[i] = rxdata2[i];
					}
				}
			}

			counter++;
		}
	}

	void print(const char *fmt, ...) {
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
