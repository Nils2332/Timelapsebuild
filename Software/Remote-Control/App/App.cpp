#include "App.h"
#include "stdio.h"

#include "System.h"
#include "gpio.h"
#include "usart.h"

#include "LCDWIKI.h"
#include "lvgl.h"

#include "math.h"

#include "adc.h"
#include "joycon.h"

#include "Gui.h"

#include "spi.h"

#include "nRF905.h"
#include "nRF905_config.h"
#include "nRF905_defs.h"
//#include "nRF905_debug.h"


//#include "simpleLCD.h"


#define RXADDR 0xFE1337AC
#define TXADDR 0xFE1337AD // Address of device to send to


joycon Joystick1(&hadc1, ADC_CHANNEL_2, ADC_CHANNEL_3, GPIOA, GPIO_PIN_7);
joycon Joystick2(&hadc1, ADC_CHANNEL_4, ADC_CHANNEL_5, GPIOC, GPIO_PIN_4);

uint32_t micros = 0;

int init_done = 0;

uint8_t worked = 0;

void InterruptPIN(uint16_t GPIO_PIN)
{
	System::print("Change Precision\n");

	if(GPIO_PIN == GPIO_PIN_4)
	{
		togglePrecision();
		System::print("Change Precision\n");
	}
}


void App_Start()
{
	System::print("TFT LCD Test2 \n");

	Joystick1.init();
	Joystick2.init();

	nRF905_init();

	// Set address of this device
	nRF905_setListenAddress(RXADDR);

	// Put into receive mode
	nRF905_RX();

	HAL_Delay(1);

	uint8_t regs[NRF905_REGISTER_COUNT];
	nRF905_getConfigRegisters(regs);

	uint16_t channel = ((uint16_t)(regs[1] & 0x01)<<8) | regs[0];
	uint32_t freq = (422400UL + (channel * 100UL)) * (1 + ((regs[1] & ~NRF905_MASK_BAND) >> 1));

	System::print("Channel: %u", channel);
	System::print("Freq: %u", freq);
	System::print("KHz");
	System::print("Auto retransmit: %u\n", !!(regs[1] & ~NRF905_MASK_AUTO_RETRAN));
	System::print("Low power RX: %u\n", !!(regs[1] & ~NRF905_MASK_LOW_RX));

	System::print("");


	lv_init();



	TFT_Init();


//	int x,y,z;
//	while(1){
//		x = readX();
//		y = readY();
//		z = readZ();
//
//		System::print("X: %d \t Y: %d \t Z: %d \n", x,y,z);
//		HAL_Delay(500);
//	}


	lv_disp_drv_t disp_drv;        		/*Descriptor of a display driver*/
	lv_disp_drv_init(&disp_drv);   		/*Basic initialization*/

	disp_drv.disp_fill = TFT_RectFill; 	/*For unbuffered drawing: LV_VDB_SIZE = 0 */
	disp_drv.disp_map = TFT_RectMap;   	/*For unbuffered drawing: LV_VDB_SIZE = 0 */
	disp_drv.disp_flush = TFT_Flush;   	/*For buffered drawing: LV_VDB_SIZE >= 0*/
	lv_disp_drv_register(&disp_drv);

	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);  		/*Basic initialization*/
	indev_drv.type = LV_INDEV_TYPE_POINTER;	/*See below.*/
	indev_drv.read = TFT_ReadTouch;			/*See below.*/
	lv_indev_drv_register(&indev_drv);  	/*Register the driver in LittlevGL*/

	disp_drv.disp_fill(0, 0, 319, 479,lv_color_hsv_to_rgb(0, 0, 0));

	lv_theme_t *th = lv_theme_night_init(210, &lv_font_dejavu_20);
	lv_theme_set_current(th);

	createView();

    init_done = 1;

    while(1){
    	lv_indev_get_act();
    	lv_task_handler();

    	HAL_Delay(10);
    	lv_tick_inc(10);
    }

}

void JoyconUpdate()
{
	Joystick1.update();
	Joystick2.update();
}

double getJoycon(uint8_t channel)
{
	double value = 0;

	if(channel == 0)value = Joystick1.joyval[0];
	if(channel == 1)value = -Joystick1.joyval[1];
	if(channel == 2)value = -Joystick2.joyval[0];
	if(channel == 3)value = Joystick2.joyval[1];

	return value;
}
