#include "LCDWIKI.h"
#include "stdio.h"
#include "stdlib.h"

#include "gpio.h"

typedef enum {
    CAL_STATE_POINT_1,
	CAL_STATE_POINT_2
}cal_state_t;
static cal_state_t cal_state;


static void RD_ACTIVE() { HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_RESET);}
static void RD_IDEL()	{ HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET);}
static void WR_ACTIVE()	{ HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);}
static void WR_IDEL()	{ HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);}
static void CD_COMMAND(){ HAL_GPIO_WritePin(LCD_CD_GPIO_Port, LCD_CD_Pin, GPIO_PIN_RESET);}
static void CD_DATA()	{ HAL_GPIO_WritePin(LCD_CD_GPIO_Port, LCD_CD_Pin, GPIO_PIN_SET);}
static void CS_ACTIVE()	{ HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);}
static void CS_IDLE()	{ HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);}
static void RST_LOW()	{ HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);}
static void RST_HIGH()	{ HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);}




static void TFT_CS_Active() { HAL_GPIO_WritePin(GPIOy, CS_PIN, GPIO_PIN_RESET); }
static void TFT_CS_Idle() { HAL_GPIO_WritePin(GPIOy, CS_PIN, GPIO_PIN_SET); }

static void WR_STROBE()	{ WR_ACTIVE(); WR_IDEL();}
static void RD_STROBE()	{RD_IDEL(); RD_ACTIVE(); RD_ACTIVE(); RD_ACTIVE();}
static void WRITE16(uint16_t d)		{uint8_t h = (d)>>8; uint8_t l = d; WRITE8(h); WRITE8(l);}
static uint16_t READ16()			{uint16_t dst; uint8_t hi; READ8(hi); READ8(); dst |= (hi << 8); return dst;}
static void WriteCmd8(uint8_t cmd)		{ CD_COMMAND(); WRITE8(cmd); CD_DATA();}
static void WriteData8(uint8_t dat)		{ WRITE8(dat);}
static void WriteCmd16(uint16_t cmd)	{ CD_COMMAND(); WRITE16(cmd); CD_DATA();}
static void WriteData16(uint16_t dat)	{ WRITE16(dat);}

void TFT_Init() {
	TFT_Reset();

	HAL_Delay(50);

	TFT_CS_Active();

    WriteCmd16(0xF9);
    TFT_WriteData(0x00);
    TFT_WriteData(0x08);
    WriteCmd16(0xC0);
    TFT_WriteData(0x19);
    TFT_WriteData(0x1A);
    WriteCmd16(0xC1);
    TFT_WriteData(0x45);
    TFT_WriteData(0X00);
    WriteCmd16(0xC2);
    TFT_WriteData(0x33);
    WriteCmd16(0xC5);
    TFT_WriteData(0x00);
    TFT_WriteData(0x28);
    WriteCmd16(0xB1);
    TFT_WriteData(0x90);
    TFT_WriteData(0x11);
    WriteCmd16(0xB4);
    TFT_WriteData(0x02);
    WriteCmd16(0xB6);
    TFT_WriteData(0x00);
    TFT_WriteData(0x42);
    TFT_WriteData(0x3B);
    WriteCmd16(0xB7);
    TFT_WriteData(0x07);
    WriteCmd16(0xE0);
    TFT_WriteData(0x1F);
    TFT_WriteData(0x25);
    TFT_WriteData(0x22);
    TFT_WriteData(0x0B);
    TFT_WriteData(0x06);
    TFT_WriteData(0x0A);
    TFT_WriteData(0x4E);
    TFT_WriteData(0xC6);
    TFT_WriteData(0x39);
    TFT_WriteData(0x00);
    TFT_WriteData(0x00);
    TFT_WriteData(0x00);
    TFT_WriteData(0x00);
    TFT_WriteData(0x00);
    TFT_WriteData(0x00);
    WriteCmd16(0xE1);
    TFT_WriteData(0x1F);
    TFT_WriteData(0x3F);
    TFT_WriteData(0x3F);
    TFT_WriteData(0x0F);
    TFT_WriteData(0x1F);
    TFT_WriteData(0x0F);
    TFT_WriteData(0x46);
    TFT_WriteData(0x49);
    TFT_WriteData(0x31);
    TFT_WriteData(0x05);
    TFT_WriteData(0x09);
    TFT_WriteData(0x03);
    TFT_WriteData(0x1C);
    TFT_WriteData(0x1A);
    TFT_WriteData(0x00);
    WriteCmd16(0xF1);
    TFT_WriteData(0x36);
    TFT_WriteData(0x04);
    TFT_WriteData(0x00);
    TFT_WriteData(0x3C);
    TFT_WriteData(0x0F);
    TFT_WriteData(0x0F);
    TFT_WriteData(0xA4);
    TFT_WriteData(0x02);
    WriteCmd16(0xF2);
    TFT_WriteData(0x18);
    TFT_WriteData(0xA3);
    TFT_WriteData(0x12);
    TFT_WriteData(0x02);
    TFT_WriteData(0x32);
    TFT_WriteData(0x12);
    TFT_WriteData(0xFF);
    TFT_WriteData(0x32);
    TFT_WriteData(0x00);
    WriteCmd16(0xF4);
    TFT_WriteData(0x40);
    TFT_WriteData(0x00);
    TFT_WriteData(0x08);
    TFT_WriteData(0x91);
    TFT_WriteData(0x04);
    WriteCmd16(0xF8);
    TFT_WriteData(0x21);
    TFT_WriteData(0x04);
    WriteCmd16(0x36);
    TFT_WriteData(0x48);
    WriteCmd16(0x3A);
    TFT_WriteData(0x55);

    WriteCmd16(0x11);    //Exit Sleep
    HAL_Delay(120);
    WriteCmd16(0x29);    //Display on


	TFT_CS_Idle();

	tft_delay(50);


	/*mirror or rotation ???*/
	TFT_CS_Active();

	WriteCmd8(0x36);
	WriteData8(0x80|0x08|0x40);

	TFT_CS_Idle();


}

static void TFT_Reset() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = RD_PIN | WR_PIN | RST_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
	TFT_SetBusOut();

	//GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin =  CD_PIN | CS_PIN ;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOy, &GPIO_InitStructure);
	TFT_SetBusOut();

	// all pins idle
	//GPIO_SetBits(GPIOy, RD_PIN | WR_PIN | RS_PIN | CS_PIN | RST_PIN);
	HAL_GPIO_WritePin(GPIOx, RD_PIN | WR_PIN | RST_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOy, CD_PIN | CS_PIN , GPIO_PIN_SET);

	//GPIO_ResetBits(GPIOy, RST_PIN);
	HAL_GPIO_WritePin(GPIOx, RST_PIN, GPIO_PIN_RESET);
	tft_delay(1);
	//GPIO_SetBits(GPIOy, RST_PIN);
	HAL_GPIO_WritePin(GPIOx, RST_PIN, GPIO_PIN_SET);
	tft_delay(5);
}


static void TFT_SetBusOut() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = 0xFF;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
}

static void TFT_SetBusIn() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = 0xFF;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
}

static uint8_t READ8() {

	RD_ACTIVE();
//	HAL_GPIO_WritePin(GPIOx, RD_PIN, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOx, RD_PIN, GPIO_PIN_SET);
//
//	//GPIO_ResetBits(GPIOy, RD_PIN); //RD active
//	HAL_GPIO_WritePin(GPIOx, RD_PIN, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOx, RD_PIN, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOx, RD_PIN, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOx, RD_PIN, GPIO_PIN_RESET);


	uint16_t res = GPIOx->IDR & 0xFF;

	/* Connection Rearrange if Pins not Syncron to port */
	uint8_t b0, b1, b2, b3, b4, b5, b6, b7;

	b0 = (res & 0b00000010) >> 1;
	b1 = (res & 0b00000001) << 1;
	b2 = (res & 0b10000000) >> 5;
	b3 = (res & 0b01000000) >> 3;
	b4 = (res & 0b00100000) >> 1;
	b5 = (res & 0b00010000) << 1;
	b6 = (res & 0b00001000) << 3;
	b7 = (res & 0b00000100) << 5;

	res = b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7;
	/*---------------------------------------*/

	RD_IDEL();
	//HAL_GPIO_WritePin(GPIOx, RD_PIN, GPIO_PIN_SET);

	return res;
}

static void WRITE8(uint8_t d) {

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

	HAL_GPIO_WritePin(GPIOx, d & 0x00FF, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOx, ~d & 0x00FF , GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOx, WR_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOx, WR_PIN, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOx, WR_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOx, WR_PIN, GPIO_PIN_SET);
//	WR_STROBE();
}

static void TFT_WriteCmd(uint8_t cmd) {
	//GPIO_ResetBits(GPIOy, RS_PIN); //switch to commands
	HAL_GPIO_WritePin(GPIOy, CD_PIN, GPIO_PIN_RESET);
	WRITE8(cmd);
}

static void TFT_WriteData(uint8_t dat) {
	//GPIO_SetBits(GPIOy, RS_PIN); //switch to data
	HAL_GPIO_WritePin(GPIOy, CD_PIN, GPIO_PIN_SET);
	WRITE8(dat);
}

static void TFT_WriteData16(uint16_t dat) {
	//GPIO_SetBits(GPIOy, RS_PIN); //switch to data
	HAL_GPIO_WritePin(GPIOy, CD_PIN, GPIO_PIN_SET);
	WRITE8(dat >> 8);
	WRITE8(dat);
}

uint16_t TFT_ReadReg(uint8_t reg) {
	TFT_CS_Active();

	TFT_WriteCmd(reg);

	TFT_SetBusIn();
	uint16_t res = READ8();

	TFT_CS_Idle();

	TFT_SetBusOut();
	return res;
}

static uint32_t TFT_SetRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	// could be optimized by not setting 0 for high byte of x
//	TFT_WriteCmd(0x02);     // columns
//	TFT_WriteData(x1 >> 8);
//	TFT_WriteCmd(0x03);
//	TFT_WriteData(x1);
//	TFT_WriteCmd(0x04);
//	TFT_WriteData(x2 >> 8);
//	TFT_WriteCmd(0x05);
//	TFT_WriteData(x2);
//	TFT_WriteCmd(0x06);     // rows
//	TFT_WriteData(y1 >> 8);
//	TFT_WriteCmd(0x07);
//	TFT_WriteData(y1);
//	TFT_WriteCmd(0x08);
//	TFT_WriteData(y2 >> 8);
//	TFT_WriteCmd(0x09);
//	TFT_WriteData(y2);
//
//	// could be optimized by not setting 0 for high byte of x
//	TFT_WriteCmd(0x80); // col addr cnt 2
//	TFT_WriteData(x1 >> 8);
//	TFT_WriteCmd(0x81);
//	TFT_WriteData(x1);
//	TFT_WriteCmd(0x82); // row addr cnt 2
//	TFT_WriteData(y1 >> 8);
//	TFT_WriteCmd(0x83);
//	TFT_WriteData(y1);

	TFT_CS_Active();

//	uint8_t x_buf[] = {x1>>8,x1&0xFF,x2>>8,x2&0xFF};
//	uint8_t y_buf[] = {y1>>8,y1&0xFF,y2>>8,y2&0xFF};
//
//	Push_Command(0x2A, x_buf, 4); //set x address
//	Push_Command(0x2B, y_buf, 4); //set y address

	WriteCmd16(0x2A);
	WriteData8(x1>>8);
	WriteData8(x1&0xFF);
	WriteData8(x2>>8);
	WriteData8(x2&0xFF);

	WriteCmd16(0x2B);
	WriteData8(y1>>8);
	WriteData8(y1&0xFF);
	WriteData8(y2>>8);
	WriteData8(y2&0xFF);

	TFT_CS_Idle();

	return ((x2-x1)+1) * ((y2-y1)+1);
}

void TFT_RectFill(int32_t x1, int32_t y1, int32_t x2, int32_t y2,  lv_color_t color) {


    uint32_t cnt = TFT_SetRect(x1, y1, x2, y2);
    TFT_CS_Active();
    TFT_WriteCmd(0x2c);

    uint16_t color16 = lv_color_to16(color);

    for (i = 0; i != cnt; i++) {
		TFT_WriteData16(color16);
    }

    TFT_CS_Idle();
}

void TFT_RectMap(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p) {


    uint32_t cnt = TFT_SetRect(x1, y1, x2, y2);
    TFT_CS_Active();
    TFT_WriteCmd(0x2c);

    for (i = 0; i != cnt; i++) {
    	TFT_WriteData16(lv_color_to16(*color_p));
    	color_p++;
    }

    TFT_CS_Idle();
}

void TFT_Flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p) {


    uint32_t cnt = TFT_SetRect(x1, y1, x2, y2);
    TFT_CS_Active();
    TFT_WriteCmd(0x2c);

    for (i = 0; i != cnt; i++) {
    	TFT_WriteData16(lv_color_to16(*color_p));
    	color_p++;
    }

    TFT_CS_Idle();

    lv_flush_ready();
}

static int compare(const void* a, const void* b) {
	return ( *(uint16_t*)a - *(uint16_t*)b );
}

uint16_t readZ() {
	HAL_GPIO_WritePin(GPIOx, PIN_XP| PIN_YN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOy, PIN_YP| PIN_XN, GPIO_PIN_RESET);


	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = PIN_XP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_YN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_YP;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOy, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_XN;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOy, &GPIO_InitStructure);

	HAL_GPIO_WritePin(GPIOx, PIN_XP, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOx, PIN_YN, GPIO_PIN_SET);

	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_YP_CH;
	sConfig.Rank = 1;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	for(int i = 0; i < 6; i++) {
		HAL_ADC_Start(hadc);
		HAL_ADC_PollForConversion(hadc, 1);
		adc_buf[i] = HAL_ADC_GetValue(hadc);
		HAL_ADC_Stop(hadc);
	}
	qsort(adc_buf, 5, sizeof(uint16_t), compare);
	uint16_t valX = adc_buf[2];

	sConfig.Channel = ADC_XN_CH;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	for(int i = 0; i < 6; i++) {
		HAL_ADC_Start(hadc);
		HAL_ADC_PollForConversion(hadc, 1);
		adc_buf[i] = HAL_ADC_GetValue(hadc);
		HAL_ADC_Stop(hadc);
	}
	qsort(adc_buf, 5, sizeof(uint16_t), compare);

	HAL_GPIO_WritePin(GPIOx, PIN_YN, GPIO_PIN_RESET);

	return ADC_MAX - (valX - adc_buf[2]);
}

uint16_t readY() {
	HAL_GPIO_WritePin(GPIOx, PIN_XP| PIN_YN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOy, PIN_YP| PIN_XN, GPIO_PIN_RESET);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = PIN_XP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_YN;
	//GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_YP;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOy, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_XN;
	//GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOy, &GPIO_InitStructure);

	HAL_GPIO_WritePin(GPIOx, PIN_XP, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOy, PIN_XN, GPIO_PIN_RESET);

	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_YP_CH;
	sConfig.Rank = 1;
	HAL_ADC_ConfigChannel(hadc, &sConfig);
	sConfig.SamplingTime = smapletime;
	for(int i = 0; i < 6; i++) {

		HAL_ADC_Start(hadc);
		HAL_ADC_PollForConversion(hadc, 1);
		adc_buf[i] = HAL_ADC_GetValue(hadc);
		HAL_ADC_Stop(hadc);
	}

	HAL_GPIO_WritePin(GPIOx, PIN_XP, GPIO_PIN_RESET);

	qsort(adc_buf, 5, sizeof(uint16_t), compare);

	return ADC_MAX - adc_buf[2];
}

uint16_t readX() {
	HAL_GPIO_WritePin(GPIOx, PIN_XP| PIN_YN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOy, PIN_YP| PIN_XN, GPIO_PIN_RESET);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = PIN_XP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	//GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_YN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_YP;
	//GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOy, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_XN;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOy, &GPIO_InitStructure);

	//HAL_GPIO_WritePin(GPIOx, PIN_YN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOy, PIN_YP, GPIO_PIN_SET);


	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_XN_CH;
	sConfig.Rank = 1;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	for(int i = 0; i < 6; i++) {
		HAL_ADC_Start(hadc);
		HAL_ADC_PollForConversion(hadc, 1);
		adc_buf[i] = HAL_ADC_GetValue(hadc);
		HAL_ADC_Stop(hadc);
	}

	HAL_GPIO_WritePin(GPIOy, PIN_YP, GPIO_PIN_RESET);

	qsort(adc_buf, 5, sizeof(uint16_t), compare);

	return ADC_MAX -  adc_buf[2];
}

static uint16_t mapX(uint16_t val) {
  return ((val - xMin) * SCREEN_WIDTH) / (xMax - xMin);
}

static uint16_t mapY(uint16_t val) {
	  return ((val - yMin) * SCREEN_HEIGHT) / (yMax - yMin);
}

bool TFT_ReadTouch(lv_indev_data_t *data) {
	//data->state = readZ() > TOUCH_Z_MIN ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
	data->state = readZ() > TOUCH_Z_MIN ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
	if (data->state == LV_INDEV_STATE_PR) {
		if (xMin == 0) {
			data->point.x = readX();
			data->point.y = readY();
		}else {
			data->point.x = mapX(readX());
			data->point.y = mapY(readY());
		}
	}
	//return pins to lcd mode
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = PIN_XP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_YN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_YP;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOy, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_XN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOy, &GPIO_InitStructure);

    return false;
}

static lv_res_t calib_btn_click(lv_obj_t *scr) {
	lv_indev_t *indev = lv_indev_get_act();

	switch(cal_state) {
	case CAL_STATE_POINT_1:
		lv_indev_get_point(indev, &cal_points[0]);
		lv_obj_set_pos(cal_cross, SCREEN_WIDTH-CROSS_OFFSET-5, SCREEN_HEIGHT-CROSS_OFFSET-5);

		cal_state = CAL_STATE_POINT_2;
		break;
	case CAL_STATE_POINT_2:
		lv_indev_get_point(indev, &cal_points[1]);

		int xRawRange = cal_points[1].x - cal_points[0].x;
		int yRawRange = cal_points[1].y - cal_points[0].y;
		int xRefRange = SCREEN_WIDTH - CROSS_OFFSET * 2;
		int yRefRange = SCREEN_HEIGHT - CROSS_OFFSET * 2;

		double xPx = xRawRange / xRefRange;
		double yPx = yRawRange / yRefRange;

		xMin = cal_points[0].x - (xPx * CROSS_OFFSET);
		yMin = cal_points[0].y - (yPx * CROSS_OFFSET);
		xMax = cal_points[1].x + (xPx * CROSS_OFFSET);
		yMax = cal_points[1].y + (yPx * CROSS_OFFSET);

		lv_scr_load(prev_scr);
		break;
	}

	return LV_RES_OK;
}

void TFT_Calibrate() {
	prev_scr = lv_scr_act();
	lv_obj_t *scr = lv_obj_create(NULL, NULL);
	lv_obj_set_size(scr, ADC_MAX, ADC_MAX);
	lv_scr_load(scr);

    lv_obj_t *cal_btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_size(cal_btn, ADC_MAX, ADC_MAX);
	lv_btn_set_style(cal_btn, LV_BTN_STYLE_REL, &lv_style_transp);
	lv_btn_set_style(cal_btn, LV_BTN_STYLE_PR, &lv_style_transp);
	lv_btn_set_action(cal_btn, LV_BTN_ACTION_CLICK, calib_btn_click);
	lv_btn_set_layout(cal_btn, LV_LAYOUT_OFF);

	static const lv_point_t p[] = {{0, 0}, {5, 5}, {10, 0},{0, 10}, {5, 5}, {10, 10}};

	cal_cross = lv_line_create(lv_scr_act(), NULL);
	lv_line_set_points(cal_cross, p, 6);

	static lv_style_t style;
	lv_style_copy(&style, &lv_style_plain);
	style.line.color = LV_COLOR_BLACK;
	style.line.width = 3;
	lv_line_set_style(cal_cross, &style);

	lv_obj_set_pos(cal_cross, CROSS_OFFSET-5, CROSS_OFFSET-5);

	cal_state = CAL_STATE_POINT_1;
}
