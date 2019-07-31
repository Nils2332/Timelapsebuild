#ifndef SRC_APP_H_
#define SRC_APP_H_

#include <stdint.h>
#include <usart.h>


#ifdef __cplusplus
extern "C" {
#endif

void InterruptPIN(uint16_t GPIO_PIN);

void Timer_IT1();

void Timer_IT2();

void Timer_IT3();

void App_Start();

void JoyconUpdate();

double getJoycon(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif /* SRC_APP_H_ */
