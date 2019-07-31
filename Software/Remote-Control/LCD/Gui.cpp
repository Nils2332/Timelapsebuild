/*
 * Gui.cpp
 *
 *  Created on: 12.03.2019
 *      Author: Nils
 */

#include "lvgl.h"
#include "stdio.h"
#include "stdlib.h"

#include "App.h"

#include "System.h"

#include "spi.h"
#include "joycon.h"

#include "Gui.h"
#include "mvm.h"
#include "settings.h"

#include "math.h"
#include "adc.h"

#define RXADDR 0xFE1337AC
#define TXADDR 0xFE1337AD // Address of device to send to



static double oldjoyvalue[4];

static uint16_t Pictures = 10;
double Frametime = 0.001;
uint8_t Picintval = 5;
uint32_t mintime = 20;
uint32_t Sessiontime = 50;

uint8_t rxdata[10];
uint8_t txdata[10];

double bat1= 3.71;
double bat2= 3.72;

double bat = 3.7;

static int32_t M1_position = 0;
static int32_t M2_position = 0;
static int32_t M3_position = 0;

uint32_t input_number = 0;

uint8_t header_size = 20;

static lv_obj_t *posjaw;
static lv_obj_t *pospitch;
static lv_obj_t *posslide;


//static lv_obj_t *header;
//lv_obj_t *page;

static lv_obj_t *bar_progrpic;
static lv_obj_t *bar_progrsession;

static lv_obj_t *lbl_number;
static lv_obj_t *lbl_battery;

static lv_obj_t *btn_pictures;
//static lv_obj_t *btn_frametime;
static lv_obj_t *btn_picinterval;
static lv_obj_t *btn_sessiontime;
static lv_obj_t *btn_en_motor;



static lv_obj_t *btn_testrun;
static lv_obj_t *btn_cycle;
static lv_obj_t *btn_pause;
static lv_obj_t *btn_start;
static lv_obj_t *btn_stop;
static lv_obj_t *btn_startpos;


static uint8_t runmode = 0;
static uint8_t positionsset = 0;
static uint8_t pause = 0;

static lv_obj_t *scr1;
static lv_obj_t *scr2;
static lv_obj_t *scr3;


uint8_t precision = 0;
uint8_t precisionmulti[2] = {70, 5};

static lv_obj_t *lbl_precision;

/*	scr1 : Main
 * 	scr2 : SetMovement
 *	scr3 : Settings
 *
 *
 */



static lv_res_t fkt_setmoveview(lv_obj_t *btn);



static lv_res_t Zero(lv_obj_t *btn);




static lv_res_t mbox1_apply_action(lv_obj_t * mbox, const char * txt);
static lv_res_t mbox2_apply_action(lv_obj_t * mbox, const char * txt);
static lv_res_t mbox3_apply_action(lv_obj_t * mbox, const char * txt);
static lv_res_t mbox_pictureno(lv_obj_t *btn);
static lv_res_t mbox_intervaltime(lv_obj_t *btn);
static lv_res_t mbox_sessiontime(lv_obj_t *btn);
static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt);


static int compare(const void* a, const void* b) {
	return ( *(uint16_t*)a - *(uint16_t*)b );
}

void togglePrecision()
{
	precision = (precision+1)%2;
	//System::print("Toggle precision: %u \n", precision);

	lv_obj_t *label = lv_obj_get_child_back(lv_scr_act(), NULL);
	lv_obj_t *label2 = lv_obj_get_child(label, NULL);

	if(precision) lv_label_set_text(label2, "FINE");
	else lv_label_set_text(label2, "COARSE");
}

void setcommandbuttons()
{
	if(positionsset){
		if(runmode == 0){
			lv_btn_set_state(btn_testrun, LV_BTN_STATE_REL);
			lv_btn_set_state(btn_startpos, LV_BTN_STATE_REL);
			lv_btn_set_state(btn_cycle, LV_BTN_STATE_REL);
			lv_btn_set_state(btn_pause, LV_BTN_STATE_INA);
			lv_btn_set_state(btn_start, LV_BTN_STATE_REL);
			lv_btn_set_state(btn_stop, LV_BTN_STATE_INA);
		}
		if(runmode == 1){
			lv_btn_set_state(btn_testrun, LV_BTN_STATE_INA);
			lv_btn_set_state(btn_startpos, LV_BTN_STATE_INA);
			lv_btn_set_state(btn_cycle, LV_BTN_STATE_INA);
			lv_btn_set_state(btn_pause, LV_BTN_STATE_INA);
			lv_btn_set_state(btn_start, LV_BTN_STATE_INA);
			lv_btn_set_state(btn_stop, LV_BTN_STATE_REL);
		}
		if(runmode == 2){
			if(pause)
			{
				lv_btn_set_state(btn_testrun, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_startpos, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_cycle, LV_BTN_STATE_REL);
				lv_btn_set_state(btn_pause, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_start, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_stop, LV_BTN_STATE_REL);
			}
			else{
				lv_btn_set_state(btn_testrun, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_startpos, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_cycle, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_pause, LV_BTN_STATE_REL);
				lv_btn_set_state(btn_start, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_stop, LV_BTN_STATE_REL);
			}
		}
		if(runmode == 4){
			if(pause)
			{
				lv_btn_set_state(btn_testrun, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_startpos, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_cycle, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_pause, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_start, LV_BTN_STATE_REL);
				lv_btn_set_state(btn_stop, LV_BTN_STATE_REL);
			}
			else{
				lv_btn_set_state(btn_testrun, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_startpos, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_cycle, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_pause, LV_BTN_STATE_REL);
				lv_btn_set_state(btn_start, LV_BTN_STATE_INA);
				lv_btn_set_state(btn_stop, LV_BTN_STATE_REL);
			}
		}
	}
	else{
		lv_btn_set_state(btn_cycle, LV_BTN_STATE_INA);
		lv_btn_set_state(btn_pause, LV_BTN_STATE_INA);
		lv_btn_set_state(btn_start, LV_BTN_STATE_INA);
		lv_btn_set_state(btn_stop, LV_BTN_STATE_INA);
		lv_btn_set_state(btn_testrun, LV_BTN_STATE_INA);
		lv_btn_set_state(btn_startpos, LV_BTN_STATE_INA);
	}
}

lv_res_t fkt_startposition(lv_obj_t *btn)
{
	fkt_mvm_startposition();
	return LV_RES_OK;
}

lv_res_t fkt_runcommand(lv_obj_t *btn)
{
	uint8_t data[5];

	data[0] = 9<<4;
	data[0] |= 6;
	if(btn == btn_testrun){
		//fkt_mvm_startposition();
		data[1] = 1;
	}
	if(btn == btn_cycle){
		data[0] = {9<<4 | 4};
		data[1] = Sessiontime>>24 & 0xFF;
		data[2] = Sessiontime>>16 & 0xFF;
		data[3] = Sessiontime>>8 & 0xFF;
		data[4] = Sessiontime & 0xFF;
		System::sendcheck(data, 5);

		HAL_Delay(10);

		data[0] = 9<<4;
		data[0] |= 6;

		data[1] = 2;
	}
	if(btn == btn_pause){
		data[1] = 3;
	}
	if(btn == btn_start){

		data[0] = {9<<4 | 4};
		data[1] = Sessiontime>>24 & 0xFF;
		data[2] = Sessiontime>>16 & 0xFF;
		data[3] = Sessiontime>>8 & 0xFF;
		data[4] = Sessiontime & 0xFF;
		System::sendcheck(data, 5);

		HAL_Delay(10);

		data[0] = {9<<4 | 5};
		data[1] = Pictures>>8 & 0xFF;
		data[2] = Pictures & 0xFF;
		System::sendcheck(data, 3);

		HAL_Delay(10);

		data[0] = 9<<4;
		data[0] |= 6;

		data[1] = 4;
	}
	if(btn == btn_stop){
		data[1] = 5;
	}

	System::sendcheck(data, 2);

	return LV_RES_OK;
}


int32_t getPosition(uint8_t axis)
{
	int32_t value = 0;

	if(axis == 0) value = M1_position;
	if(axis == 1) value = M2_position;
	if(axis == 2) value = M3_position;

	return value;
}

static lv_res_t mbox1_apply_action(lv_obj_t * mbox, const char * txt)
{
	if(strcmp(txt,"Apply")==0){
		Pictures = input_number;
		lv_obj_clean(btn_pictures);
		lv_obj_clean(btn_sessiontime);

		char buffer[20];
	    lv_obj_t *label = lv_label_create(btn_pictures, NULL);
		sprintf(buffer, "%4.0f", (double)Pictures);
		lv_label_set_text(label, buffer);

		Sessiontime = Pictures * Picintval;
		label = lv_label_create(btn_sessiontime, NULL);
		sprintf(buffer, "%2.0f:%02.0f:%02.0f", (double)(Sessiontime/3600), (double)((Sessiontime/60)%60), (double)(Sessiontime%60));
		lv_label_set_text(label, buffer);
	}

    lv_obj_t * mbox1 = lv_mbox_get_from_btn(mbox);

    lv_mbox_start_auto_close(mbox1, 1);

    return LV_RES_OK; /*Return OK if the message box is not deleted*/
}

static lv_res_t mbox2_apply_action(lv_obj_t * mbox, const char * txt)
{
	if(strcmp(txt,"Apply")==0){
		Picintval = input_number;
		if(Picintval < 2) Picintval = 2;
		lv_obj_clean(btn_picinterval);
		lv_obj_clean(btn_sessiontime);

		char buffer[20];
	    lv_obj_t *label = lv_label_create(btn_picinterval, NULL);
		sprintf(buffer, "%4.0f", (double)Picintval);
		lv_label_set_text(label, buffer);

		Sessiontime = Pictures * Picintval;
		label = lv_label_create(btn_sessiontime, NULL);
		sprintf(buffer, "%2.0f:%02.0f:%02.0f", (double)(Sessiontime/3600), (double)((Sessiontime/60)%60), (double)(Sessiontime%60));
		lv_label_set_text(label, buffer);
	}

    lv_obj_t * mbox1 = lv_mbox_get_from_btn(mbox);

    lv_mbox_start_auto_close(mbox1, 1);

    return LV_RES_OK; /*Return OK if the message box is not deleted*/
}

static lv_res_t mbox3_apply_action(lv_obj_t * mbox, const char * txt)
{
	if(strcmp(txt,"Apply")==0){
		Sessiontime = (input_number/10000)*3600+((input_number%10000)/100)*60+(input_number%100);
		uint32_t test_picintval = Sessiontime/Pictures;

		if(test_picintval<2){
			Picintval = 2;
			Pictures = Sessiontime/Picintval;
			Sessiontime = Picintval * Pictures;
		}
		else{
			Picintval = test_picintval;
			Sessiontime = Picintval * Pictures;
		}

//		lv_obj_clean(btn_pictures);
//		lv_obj_clean(btn_picinterval);
//		lv_obj_clean(btn_sessiontime);


		char buffer[20];
	    lv_obj_t *label = lv_obj_get_child(btn_picinterval, NULL);//lv_label_create(btn_picinterval, NULL);
		sprintf(buffer, "%4.0f", (double)Picintval);
		lv_label_set_text(label, buffer);

	    label = lv_obj_get_child(btn_pictures, NULL);//lv_label_create(btn_pictures, NULL);
		sprintf(buffer, "%4.0f", (double)Pictures);
		lv_label_set_text(label, buffer);


		Sessiontime = Pictures * Picintval;
		label = lv_obj_get_child(btn_sessiontime, NULL);
		sprintf(buffer, "%2.0f:%02.0f:%02.0f", (double)(Sessiontime/3600), (double)((Sessiontime/60)%60), (double)(Sessiontime%60));
		lv_label_set_text(label, buffer);
	}

    lv_obj_t * mbox1 = lv_mbox_get_from_btn(mbox);

    lv_mbox_start_auto_close(mbox1, 1);

    return LV_RES_OK; /*Return OK if the message box is not deleted*/
}

static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt)
{
	if(strcmp(txt,"Delete")==0){
		input_number /= 10;
	}
	else if(strcmp(txt,"Clear")==0){
		input_number = 0;
	}
	else{
		input_number = input_number*10 + atoi(txt);
	}

	char buffer[50];
	sprintf(buffer, "%6.0f", (double)input_number);
	lv_label_set_text(lbl_number, buffer);

    return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static lv_res_t mbox_pictureno(lv_obj_t *btn)
{
	lv_obj_t * mbox1 = lv_mbox_create(lv_scr_act(), NULL);
	lv_mbox_set_text(mbox1, "Set No. of Pictures");                    /*Set the text*/

	lv_obj_set_width(mbox1, LV_HOR_RES-10);
	lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/

	input_number = Pictures;

	lbl_number = lv_label_create(mbox1, NULL);
	lv_obj_align(lbl_number, mbox1, LV_ALIGN_CENTER, 0, 0);
	char buffer[20];
	sprintf(buffer, "%6.0f", (double)input_number);
	lv_label_set_text(lbl_number, buffer);

	static const char * btnm_map[] = {"1", "2", "3", "4", "5", "\n",
	                           "6", "7", "8", "9", "0", "\n",
	                           "Delete", "Clear", ""};

	/*Create a default button matrix*/
	lv_obj_t * btnm1 = lv_btnm_create(mbox1, NULL);
	lv_btnm_set_map(btnm1, btnm_map);
	lv_btnm_set_action(btnm1, btnm_action);
	lv_obj_set_size(btnm1, LV_HOR_RES-16, LV_VER_RES / 2);
	lv_obj_align(btnm1, lbl_number, LV_ALIGN_OUT_BOTTOM_MID, 0 ,0);

	static const char * btns[] ={"Cancel", "Apply", ""}; /*Button description. '\221' lv_btnm like control char*/
	lv_mbox_add_btns(mbox1, btns, NULL);
	lv_mbox_set_action(mbox1, mbox1_apply_action);

	lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/

	lv_mbox_set_anim_time(mbox1, 0);

	return LV_RES_INV;
}

static lv_res_t mbox_intervaltime(lv_obj_t *btn)
{

	lv_obj_t * mbox1 = lv_mbox_create(lv_scr_act(), NULL);
	lv_mbox_set_text(mbox1, "Set Intervaltime \n"
							"in Seconds (min 2)");                    /*Set the text*/

	lv_obj_set_width(mbox1, LV_HOR_RES-10);
	lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/

	input_number = Picintval;

	lbl_number = lv_label_create(mbox1, NULL);
	lv_obj_align(lbl_number, mbox1, LV_ALIGN_CENTER, 0, 0);
	char buffer[20];
	sprintf(buffer, "%6.0f", (double)input_number);
	lv_label_set_text(lbl_number, buffer);

	static const char * btnm_map[] = {"1", "2", "3", "4", "5", "\n",
	                           "6", "7", "8", "9", "0", "\n",
	                           "Delete", "Clear", ""};

	/*Create a default button matrix*/
	lv_obj_t * btnm1 = lv_btnm_create(mbox1, NULL);
	lv_btnm_set_map(btnm1, btnm_map);
	lv_btnm_set_action(btnm1, btnm_action);
	lv_obj_set_size(btnm1, LV_HOR_RES-16, LV_VER_RES / 2);
	lv_obj_align(btnm1, lbl_number, LV_ALIGN_OUT_BOTTOM_MID, 0 ,0);

	static const char * btns[] ={"Cancel", "Apply", ""}; /*Button description. '\221' lv_btnm like control char*/
	lv_mbox_add_btns(mbox1, btns, NULL);
	lv_mbox_set_action(mbox1, mbox2_apply_action);

	lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/

	lv_mbox_set_anim_time(mbox1, 0);

	return LV_RES_INV;
}

static lv_res_t mbox_sessiontime(lv_obj_t *btn)
{

	lv_obj_t * mbox1 = lv_mbox_create(lv_scr_act(), NULL);
	lv_mbox_set_text(mbox1, "Set Session Time \n"
							"hh:mm:ss");                    /*Set the text*/

	lv_obj_set_width(mbox1, LV_HOR_RES-10);
	lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/

	input_number = (Sessiontime/3600)*10000+(Sessiontime%3600/60)*100+Sessiontime%60;

	lbl_number = lv_label_create(mbox1, NULL);
	lv_obj_align(lbl_number, mbox1, LV_ALIGN_CENTER, 0, 0);
	char buffer[20];
	sprintf(buffer, "%6.0f", (double)input_number);
	lv_label_set_text(lbl_number, buffer);

	static const char * btnm_map[] = {"1", "2", "3", "4", "5", "\n",
	                           "6", "7", "8", "9", "0", "\n",
	                           "Delete", "Clear", ""};

	/*Create a default button matrix*/
	lv_obj_t * btnm1 = lv_btnm_create(mbox1, NULL);
	lv_btnm_set_map(btnm1, btnm_map);
	lv_btnm_set_action(btnm1, btnm_action);
	lv_obj_set_size(btnm1, LV_HOR_RES-16, LV_VER_RES / 2);
	lv_obj_align(btnm1, lbl_number, LV_ALIGN_OUT_BOTTOM_MID, 0 ,0);

	static const char * btns[] ={"Cancel", "Apply", ""}; /*Button description. '\221' lv_btnm like control char*/
	lv_mbox_add_btns(mbox1, btns, NULL);
	lv_mbox_set_action(mbox1, mbox3_apply_action);

	lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/

	lv_mbox_set_anim_time(mbox1, 0);

	return LV_RES_INV;
}

lv_res_t fkt_return(lv_obj_t *btn)
{
	if(lv_scr_act() == scr2){
		sendpoints();
		HAL_Delay(10);

		uint8_t data[5];
		data[0] = {9<<4 | 8};
		System::sendrecieve(data, 1, rxdata, 5);

		uint32_t mintime = rxdata[1]<<24 | rxdata[2]<<16 | rxdata[3]<<8 | rxdata[4];
		mintime /= 100;
		System::print("mintime %u \n", mintime);

		/*Check minimal Time and adjust Sessiontime*/
		if(mintime > Sessiontime){
			Sessiontime = mintime;

			uint32_t test_picintval = Sessiontime/Pictures;

			if(test_picintval<2){
				Picintval = 2;
				Pictures = Sessiontime/Picintval;
				Sessiontime = Picintval * Pictures;
			}
			else{
				Picintval = test_picintval;
				Sessiontime = Picintval * Pictures;
			}

			char buffer[20];
		    lv_obj_t *label = lv_obj_get_child(btn_picinterval, NULL);//lv_label_create(btn_picinterval, NULL);
			sprintf(buffer, "%4.0f", (double)Picintval);
			lv_label_set_text(label, buffer);

		    label = lv_obj_get_child(btn_pictures, NULL);//lv_label_create(btn_pictures, NULL);
			sprintf(buffer, "%4.0f", (double)Pictures);
			lv_label_set_text(label, buffer);


			Sessiontime = Pictures * Picintval;
			label = lv_obj_get_child(btn_sessiontime, NULL);
			sprintf(buffer, "%2.0f:%02.0f:%02.0f", (double)(Sessiontime/3600), (double)((Sessiontime/60)%60), (double)(Sessiontime%60));
			lv_label_set_text(label, buffer);
		}

		HAL_Delay(10);

		/*Send Sessiontime*/
		data[0] = {9<<4 | 4};
		data[1] = Sessiontime>>24 & 0xFF;
		data[2] = Sessiontime>>16 & 0xFF;
		data[3] = Sessiontime>>8 & 0xFF;
		data[4] = Sessiontime & 0xFF;
		System::sendcheck(data, 5);

		HAL_Delay(10);

		/*Send Pictures*/
		data[0] = {9<<4 | 5};
		data[1] = Pictures>>8 & 0xFF;
		data[2] = Pictures & 0xFF;
		System::sendcheck(data, 3);

	}
	lv_scr_load(scr1);
	return LV_RES_OK;
}

static lv_res_t fkt_setmoveview(lv_obj_t *btn)
{
	lv_scr_load(scr2);
	return LV_RES_OK;
}

static lv_res_t fkt_setsettings(lv_obj_t *btn)
{
	lv_scr_load(scr3);
	return LV_RES_OK;
}

lv_res_t fkt_motorpw_action(lv_obj_t * btn)
{
	uint8_t data[1];
	data[0] = {9<<4 | 9};
	System::sendcheck(data, 1);

	return LV_RES_OK;
}


static lv_res_t Zero(lv_obj_t *btn)
{
	uint8_t data[7];

	/*Jaw*/
	int32_t buffer = 0;
	data[0] = 0<<4;
	data[0] |= 2;
	data[1] = buffer >> 24;
	data[2] = buffer >> 16;
	data[3] = buffer >> 8;
	data[4] = buffer;
	data[5] = 100;
	data[6] = 1;
	System::sendcheck(data, 7);

	/*Pitch*/
	data[0] = 1<<4;
	data[0] |= 2;
	System::sendcheck(data, 7);

	/*Slide*/
	buffer = 25000*4;
	data[0] = 2<<4;
	data[0] |= 2;
	data[1] = buffer >> 24;
	data[2] = buffer >> 16;
	data[3] = buffer >> 8;
	data[4] = buffer;

	System::sendcheck(data, 7);
	return LV_RES_OK;
}



void createView()
{
	scr1 = lv_obj_create(NULL, NULL);
	scr2 = lv_obj_create(NULL, NULL);
	scr3 = lv_obj_create(NULL, NULL);


	lv_obj_t *header = lv_cont_create(scr1, NULL);
	lv_obj_set_size(header, LV_HOR_RES, header_size);

	lv_obj_t *page = lv_cont_create(scr1, NULL);
	lv_obj_set_size(page, LV_HOR_RES, LV_VER_RES - header_size);
	lv_obj_align(page, header, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

	createHeader(header);
	createMain(page);


	lv_obj_t *header2 = lv_cont_create(scr2, header);
	lv_obj_t *page2 = lv_cont_create(scr2, page);

	createHeader(header2);
	createMoveGraph(page2);

	lv_obj_t *header3 = lv_cont_create(scr3, header);
	lv_obj_t *page3 = lv_cont_create(scr3, page);

	createHeader(header3);
	createSettings(page3);


	lv_scr_load(scr1);

	lv_task_create(label_refresher_task, 400, LV_TASK_PRIO_MID, NULL);
	lv_task_create(readJoycon_task, 100, LV_TASK_PRIO_MID, NULL);
	lv_task_create(mvm_refresher_task, 50, LV_TASK_PRIO_LOW, NULL);
	lv_task_create(battery_refresher, 1000, LV_TASK_PRIO_LOW, NULL);


}

void battery_refresher(void * p)
{
	uint16_t adc_buf[5];

	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 1;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	for(int i = 0; i < 6; i++) {
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 1);
		adc_buf[i] = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
	}


	qsort(adc_buf, 5, sizeof(uint16_t), compare);
	bat = adc_buf[2];

	bat = (double)bat * 4.233 / 1000;
	System::print("Batterie: %1.2fV \n", bat);


	txdata[0] = 0<<4 | 11;
	System::sendrecieve(txdata, 1, rxdata, 5);
	bat1 = rxdata[1] <<8 | rxdata[2];
	bat2 = rxdata[3] <<8 | rxdata[4];
	bat1 /= 1000;
	bat2 /= 1000;



	lv_obj_t *label = lv_obj_get_child_back(lv_scr_act(), NULL);
	lv_obj_t *label2 = lv_obj_get_child_back(label, NULL);

	char buffer[50];
	sprintf(buffer, "%0.2fV %0.2fV       %0.2fV", bat1, bat2, bat);
	lv_label_set_text(label2, buffer);
}


void readJoycon_task(void * p)
{
	JoyconUpdate();

	uint8_t data[2];
	data[0] = 1;

	if(abs(getJoycon(0) - oldjoyvalue[0])>0.01){
		oldjoyvalue[0] = getJoycon(0);
		data[0] |= 0<<4;
		data[1] = (int8_t)(oldjoyvalue[0]*precisionmulti[precision]);
		System::sendcheck(data, 2);
	}

	if(abs(getJoycon(1) - oldjoyvalue[1])>0.01){
		oldjoyvalue[1] = getJoycon(1);
		data[0] |= 1<<4;
		data[1] = (int8_t)(-oldjoyvalue[1]*precisionmulti[precision]);
		System::sendcheck(data, 2);
	}

	if(abs(getJoycon(2) - oldjoyvalue[2])>0.01){
		oldjoyvalue[2] = getJoycon(2);
		data[0] |= 2<<4;
		data[1] = (int8_t)(oldjoyvalue[2]*precisionmulti[precision]);
		System::sendcheck(data, 2);
	}
}


void label_calcpositions_task(void * p)
{
	//M1.update();
}

void label_refresher_task(void * p)
{
	char buffer[30];
	sprintf(buffer, "%0.2fV %0.2fV", bat1, bat2);
	lv_label_set_text(lbl_battery, buffer);

	txdata[0] = 0<<4 | 10;
	System::sendrecieve(txdata, 1, rxdata, 9);
	if(rxdata[0] == 10 && rxdata[1]==0){
		M1_position = rxdata[2]<<24 | rxdata[3]<<16 | rxdata[4]<<8 | rxdata[5];
		M1_position /=4;
	}

	runmode = rxdata[6] & 0x0F;
	positionsset = rxdata[6]>>4 & 0b01;
	pause = rxdata[6]>>5 & 0b01;
	uint8_t motormode = rxdata[6]>>6;


	uint8_t progsess = rxdata[7];
	uint8_t progpic = rxdata[8];

	lv_bar_set_value(bar_progrpic, progpic);
	lv_bar_set_value(bar_progrsession, progsess);



	HAL_Delay(10);
	txdata[0] = 1<<4 | 10;
	System::sendrecieve(txdata, 1, rxdata, 8);
	if(rxdata[0] == 10 && rxdata[1]==1){
		M2_position = rxdata[2]<<24 | rxdata[3]<<16 | rxdata[4]<<8 | rxdata[5];
		M2_position /=4;
	}

	HAL_Delay(10);
	txdata[0] = 2<<4 | 10;
	System::sendrecieve(txdata, 1, rxdata, 8);
	if(rxdata[0] == 10 && rxdata[1]==2){
		M3_position = rxdata[2]<<24 | rxdata[3]<<16 | rxdata[4]<<8 | rxdata[5];
		M3_position /=4;
	}

	if(lv_obj_get_screen(btn_en_motor) == lv_scr_act()){
		lv_obj_t *label = lv_obj_get_child(btn_en_motor, NULL);
		if(motormode == 0){
			lv_label_set_text(label, "Disconn.");
			lv_btn_set_state(btn_en_motor, LV_BTN_STATE_INA);
		}
		if(motormode == 1){
			lv_label_set_text(label, "Motor OFF");
			lv_btn_set_state(btn_en_motor, LV_BTN_STATE_REL);
		}
		if(motormode == 2){
			lv_label_set_text(label, "Motor ON");
			lv_btn_set_state(btn_en_motor, LV_BTN_STATE_REL);
		}
	}

	if(lv_scr_act() == scr2){
		fkt_btn_motor2(motormode);
		mvm_position_update();
	}

	setcommandbuttons();

	if(lv_obj_get_screen(posjaw) == lv_scr_act()) {

		sprintf(buffer, "Pos Jaw: %6.0f   %2.2f", (double)M1_position, (double)M1_position*0.01125);
		lv_label_set_text(posjaw, buffer);
	}

	if(lv_obj_get_screen(pospitch) == lv_scr_act()) {
		sprintf(buffer, "Pos Pitch:\t%6.0f   %2.2f", (double)M2_position, (double)M2_position*0.01125);
		lv_label_set_text(pospitch, buffer);
	}

	if(lv_obj_get_screen(posslide) == lv_scr_act()) {
		sprintf(buffer, "Pos Slide:\t%6.0f   %4.1f", (double)M3_position, (double)M3_position*0.015);
		lv_label_set_text(posslide, buffer);
	}

	lv_obj_t *label = lv_obj_get_child_back(lv_scr_act(), NULL);
	lv_obj_t *label2 = lv_obj_get_child(label, NULL);

	if(precision) lv_label_set_text(label2, "FINE");
	else lv_label_set_text(label2, "COARSE");

}

void createHeader(lv_obj_t * parent)
{
	static lv_style_t style_txt;
	lv_style_copy(&style_txt, lv_obj_get_style(parent));
	style_txt.text.font = &lv_font_dejavu_10;
	lv_obj_set_style(parent, &style_txt);

	lbl_battery = lv_label_create(parent, NULL);
	lv_obj_align(lbl_battery, parent, LV_ALIGN_IN_LEFT_MID, 25, 0);
	char buffer[50];
	sprintf(buffer, "%0.2fV %0.2fV       %0.2fV", bat1, bat2, bat);
	lv_label_set_text(lbl_battery, buffer);

	lv_obj_t *label = lv_label_create(parent, NULL);
	lv_obj_align(label, parent, LV_ALIGN_IN_LEFT_MID, 5 , 0);
	lv_label_set_text(label, SYMBOL_BATTERY_FULL);

	lbl_precision = lv_label_create(parent, NULL);
	lv_obj_align(lbl_precision, parent, LV_ALIGN_IN_RIGHT_MID, -20, 0);
	if(precision) lv_label_set_text(lbl_precision, "FINE");
	else lv_label_set_text(lbl_precision, "COARSE");

}

void createMain(lv_obj_t * parent)
{
	uint8_t button_height = 42;

	/* Button Motor ON*/
    btn_en_motor = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_en_motor, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_en_motor, parent, LV_ALIGN_IN_TOP_LEFT, 5, 0);
    lv_btn_set_action(btn_en_motor, LV_BTN_ACTION_CLICK, fkt_motorpw_action);
    lv_btn_set_state(btn_en_motor, LV_BTN_STATE_INA);

    lv_obj_t *label = lv_label_create(btn_en_motor, NULL);
    lv_label_set_text(label, "Disconn.");


    lv_obj_t *btn_zero = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_zero, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_zero, btn_en_motor, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_zero, LV_BTN_ACTION_CLICK, Zero);

    label = lv_label_create(btn_zero, NULL);
    lv_label_set_text(label, "ZERO");


    /* Show Position */
    char buffer[50];
    posjaw = lv_label_create(parent, NULL);
    sprintf(buffer, "Pos Jaw: %6.0f   %2.2f", (double)M1_position, (double)M1_position*0.01125);
    lv_label_set_text(posjaw, buffer);
    lv_obj_align(posjaw, btn_en_motor, LV_ALIGN_OUT_BOTTOM_LEFT, 0 , 0);

    pospitch = lv_label_create(parent, NULL);
    sprintf(buffer, "Pos Pitch:\t%6.0f   %2.2f", (double)M2_position, (double)M2_position*0.01125);
    lv_label_set_text(pospitch, buffer);
    lv_obj_align(pospitch, posjaw, LV_ALIGN_OUT_BOTTOM_LEFT, 0 , 0);

    posslide = lv_label_create(parent, NULL);
    sprintf(buffer, "Pos Slide:\t%6.0f   %4.1f", (double)M3_position, (double)M3_position*0.015);
    lv_label_set_text(posslide, buffer);
    lv_obj_align(posslide, pospitch, LV_ALIGN_OUT_BOTTOM_LEFT, 0 , 0);


    /* Button SetMovment*/
    lv_obj_t *btn_setmovemnt = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_setmovemnt, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_setmovemnt, posslide, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_btn_set_action(btn_setmovemnt, LV_BTN_ACTION_CLICK, fkt_setmoveview);

    label = lv_label_create(btn_setmovemnt, NULL);
    lv_label_set_text(label, "Set Movement");


    /* Button Settings*/
    lv_obj_t *btn_settings = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_settings, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_settings, btn_setmovemnt, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_settings, LV_BTN_ACTION_CLICK, fkt_setsettings);

    label = lv_label_create(btn_settings, NULL);
    lv_label_set_text(label, SYMBOL_SETTINGS);


    /* Button SetPictures*/
    btn_pictures = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_pictures, LV_HOR_RES-10-130, button_height);
    lv_obj_align(btn_pictures, btn_setmovemnt, LV_ALIGN_OUT_BOTTOM_LEFT, 130, 0);
    lv_btn_set_action(btn_pictures, LV_BTN_ACTION_CLICK, mbox_pictureno);

    label = lv_label_create(btn_pictures, NULL);
	sprintf(buffer, "%4.0f", (double)Pictures);
	lv_label_set_text(label, buffer);

	label = lv_label_create(parent, NULL);
	lv_label_set_text(label, "Pictures:   ");
	lv_obj_align(label, btn_pictures, LV_ALIGN_OUT_LEFT_MID, 0, 0);


	/* Button SetTime Picture*/
	btn_picinterval = lv_btn_create(parent, NULL);
	lv_obj_set_size(btn_picinterval, LV_HOR_RES-10-130, button_height);
	lv_obj_align(btn_picinterval, btn_pictures, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
	lv_btn_set_action(btn_picinterval, LV_BTN_ACTION_CLICK, mbox_intervaltime);

	label = lv_label_create(btn_picinterval, NULL);
	sprintf(buffer, "%3.0f", (double)Picintval);
	lv_label_set_text(label, buffer);

	label = lv_label_create(parent, NULL);
	lv_label_set_text(label, "Intervalltime: ");
	lv_obj_align(label, btn_picinterval, LV_ALIGN_OUT_LEFT_MID, 0, 0);


	/* Button SetTime Session*/
	btn_sessiontime = lv_btn_create(parent, NULL);
	lv_obj_set_size(btn_sessiontime, LV_HOR_RES-10-130, button_height);
	lv_obj_align(btn_sessiontime, btn_picinterval, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
	lv_btn_set_action(btn_sessiontime, LV_BTN_ACTION_CLICK, mbox_sessiontime);

	label = lv_label_create(btn_sessiontime, NULL);
	sprintf(buffer, "%2.0f:%02.0f:%02.0f", (double)(Sessiontime/3600), (double)((Sessiontime/60)%60), (double)(Sessiontime%60));
	lv_label_set_text(label, buffer);

	label = lv_label_create(parent, NULL);
	lv_label_set_text(label, "Sessiontime: ");
	lv_obj_align(label, btn_sessiontime, LV_ALIGN_OUT_LEFT_MID, 0, 0);



    /* Button Testrun*/
    btn_testrun = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_testrun, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_testrun, btn_sessiontime, LV_ALIGN_OUT_BOTTOM_LEFT, -130, 0);
    lv_btn_set_action(btn_testrun, LV_BTN_ACTION_CLICK, fkt_runcommand);
    lv_btn_set_state(btn_testrun, LV_BTN_STATE_INA);

    label = lv_label_create(btn_testrun, NULL);
	lv_label_set_text(label, "Testrun");


    /* Button Startpos*/
    btn_startpos = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_startpos, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_startpos, btn_testrun, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_startpos, LV_BTN_ACTION_CLICK, fkt_startposition);
    lv_btn_set_state(btn_startpos, LV_BTN_STATE_INA);

    label = lv_label_create(btn_startpos, NULL);
	lv_label_set_text(label, "Startpositon");


    /* Button Cycle*/
    btn_cycle = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_cycle, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_cycle, btn_testrun, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_btn_set_action(btn_cycle, LV_BTN_ACTION_CLICK, fkt_runcommand);
    lv_btn_set_state(btn_cycle, LV_BTN_STATE_INA);

    label = lv_label_create(btn_cycle, NULL);
	lv_label_set_text(label, "Cycle");


    /* Button PauseC*/
    btn_pause = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_pause, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_pause, btn_cycle, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_pause, LV_BTN_ACTION_CLICK, fkt_runcommand);
    lv_btn_set_state(btn_pause, LV_BTN_STATE_INA);

    label = lv_label_create(btn_pause, NULL);
	lv_label_set_text(label, "Pause");


    /* Button Start*/
    btn_start = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_start, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_start, btn_cycle, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_btn_set_action(btn_start, LV_BTN_ACTION_CLICK, fkt_runcommand);
    lv_btn_set_state(btn_start, LV_BTN_STATE_INA);

    label = lv_label_create(btn_start, NULL);
	lv_label_set_text(label, "Start");


    /* Button Stop*/
    btn_stop = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_stop, (LV_HOR_RES-10)/2, button_height);
    lv_obj_align(btn_stop, btn_start, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_stop, LV_BTN_ACTION_CLICK, fkt_runcommand);
    lv_btn_set_state(btn_stop, LV_BTN_STATE_INA);

    label = lv_label_create(btn_stop, NULL);
	lv_label_set_text(label, "Stop");


	/*Progress Bar Picture*/
	bar_progrpic = lv_bar_create(parent, NULL);
	lv_obj_set_size(bar_progrpic, LV_HOR_RES-10, 10);
	lv_obj_align(bar_progrpic, btn_start, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 5);
	lv_bar_set_value(bar_progrpic, 0);


	/*Progress Bar Session*/
	bar_progrsession = lv_bar_create(parent, NULL);
	lv_obj_set_size(bar_progrsession, LV_HOR_RES-10, 10);
	lv_obj_align(bar_progrsession, bar_progrpic, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);
	lv_bar_set_value(bar_progrsession, 0);
}
