#ifndef LCDWIKI_H_
#define LCDWIKI_H_

#include "gpio.h"
#include "lvgl.h"
#include "adc.h"


#ifdef __cplusplus
extern "C" {
#endif

static GPIO_TypeDef *GPIOy=GPIOA;

/* A */
#define CD_PIN GPIO_PIN_0  //RS == CD
#define CS_PIN GPIO_PIN_1

/*8 Parralel Data Pins*/
static GPIO_TypeDef *GPIOx=GPIOB;

/* B */
#define RD_PIN GPIO_PIN_12
#define WR_PIN GPIO_PIN_13
#define RST_PIN GPIO_PIN_14
//#define BKLT_PIN GPIO_PIN_13


static ADC_HandleTypeDef* hadc = &hadc1;
static uint32_t smapletime = ADC_SAMPLETIME_3CYCLES;

//ADC12
#define PIN_YP CD_PIN // PORTB y+ ADC8  WR		GPIOy		GPIO_PIN_1 -> Channel 9
#define PIN_XN CS_PIN // PORTB x- ADC9  RS		GPIOy		GPIO_PIN_0 -> Channel 8
#define PIN_YN GPIO_PIN_1 // PORTA x+ ADC6  D6	GPIOx
#define PIN_XP GPIO_PIN_0 // PORTA y- ADC7  D7	GPIOx


#define ADC_YP_CH ADC_CHANNEL_0
#define ADC_XN_CH ADC_CHANNEL_1

#define ADC_MAX 4095
#define TOUCH_Z_MIN 500 //higher then this is considered a touch

#define SCREEN_WIDTH 319
#define SCREEN_HEIGHT 479
#define CROSS_OFFSET 40

// PUBLIC functions
void TFT_Init();
uint16_t TFT_ReadReg(uint8_t reg);
void TFT_RectFill(int32_t x1, int32_t y1, int32_t x2, int32_t y2,  lv_color_t color);
void TFT_RectMap(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
void TFT_Flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
void TFT_Calibrate();
bool TFT_ReadTouch(lv_indev_data_t *data);

// PRIVATE functions
static void RD_ACTIVE();
static void RD_IDEL();
static void WR_ACTIVE();
static void WR_IDEL();
static void CD_COMMAND();
static void CD_DATA();
static void CS_ACTIVE();
static void CS_IDLE();
static void RST_LOW();
static void RST_HIGH();


static void WR_STROBE();
static void RD_STROBE();


static void WRITE16(uint16_t d);
static uint16_t READ16();
static void WriteCmd8(uint8_t cmd);
static void WriteData8(uint8_t dat);
static void WriteCmd16(uint16_t cmd);
static void WriteData16(uint16_t dat);


static void TFT_Reset();
static void TFT_CS_Active();
static void TFT_CS_Idle();
static void TFT_SetBusOut();
static void TFT_SetBusIn();
static uint8_t READ8();
static void WRITE8(uint8_t d);

static void TFT_WriteData(uint8_t dat);
static void TFT_WriteCmd(uint8_t cmd);
static void TFT_WriteData16(uint16_t dat);

static uint32_t TFT_SetRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
 uint16_t readZ();
 uint16_t readX();
 uint16_t readY();
static lv_res_t calib_btn_click(lv_obj_t *scr);

// VARS
void (*tft_delay)(); // pointer to a us delay function
static uint32_t i;
static uint16_t adc_buf[5];
static lv_obj_t *prev_scr;
static lv_obj_t *cal_cross;
static lv_point_t cal_points[2];
static uint16_t xMin=3600;
static uint16_t yMin=300;
static uint16_t xMax=470;
static uint16_t yMax=3700;
static uint16_t lastx=0;
static uint16_t lasty=0;

#ifdef __cplusplus
}
#endif

#endif /* LCDWIKI_H_ */
