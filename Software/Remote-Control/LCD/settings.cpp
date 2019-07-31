/*
 * settings.cpp
 *
 *  Created on: 02.04.2019
 *      Author: Nils
 */
#include "settings.h"
#include "Gui.h"

#include "math.h"
#include "lvgl.h"
#include "joycon.h"
#include "App.h"

#include "System.h"

static lv_res_t fkt_Jaw_min(lv_obj_t *btn);
static lv_res_t fkt_Jaw_max(lv_obj_t *btn);
static lv_res_t fkt_Pitch_min(lv_obj_t *btn);
static lv_res_t fkt_Pitch_max(lv_obj_t *btn);
static lv_res_t fkt_Slide_min(lv_obj_t *btn);
static lv_res_t fkt_Slide_max(lv_obj_t *btn);



static lv_res_t fkt_Jaw_min(lv_obj_t *btn){
	uint8_t data[6];
	int32_t buffer = -11111*4;		//125/0.01125
	data[0] = 0;
	data[0] |= 0<<4;
	data[0] |= 2;
	data[1] = buffer >> 24;
	data[2] = buffer >> 16;
	data[3] = buffer >> 8;
	data[4] = buffer;
	data[5] = 100;
	System::sendcheck(data, 6);

	return LV_RES_OK;
}
static lv_res_t fkt_Jaw_max(lv_obj_t *btn)
{
	uint8_t data[6];
	int32_t buffer = 11111*4;	//125/0.01125
	data[0] = 0;
	data[0] |= 0<<4;
	data[0] |= 2;
	data[1] = buffer >> 24;
	data[2] = buffer >> 16;
	data[3] = buffer >> 8;
	data[4] = buffer;
	data[5] = 100;
	System::sendcheck(data, 6);

	return LV_RES_OK;
}
static lv_res_t fkt_Pitch_min(lv_obj_t *btn)
{
	uint8_t data[6];
	int32_t buffer = -8088*4;		//92/0.01125
	data[0] = 0;
	data[0] |= 1<<4;
	data[0] |= 2;
	data[1] = buffer >> 24;
	data[2] = buffer >> 16;
	data[3] = buffer >> 8;
	data[4] = buffer;
	data[5] = 100;
	System::sendcheck(data, 6);

	return LV_RES_OK;
}
static lv_res_t fkt_Pitch_max(lv_obj_t *btn)
{
	uint8_t data[6];
	int32_t buffer = 8088*4;		//92/0.01125
	data[0] = 0;
	data[0] |= 1<<4;
	data[0] |= 2;
	data[1] = buffer >> 24;
	data[2] = buffer >> 16;
	data[3] = buffer >> 8;
	data[4] = buffer;
	data[5] = 100;
	System::sendcheck(data, 6);

	return LV_RES_OK;
}
static lv_res_t fkt_Slide_min(lv_obj_t *btn)
{
	uint8_t data[6];
	int32_t buffer = 0;
	data[0] = 0;
	data[0] |= 2<<4;
	data[0] |= 2;
	data[1] = buffer >> 24;
	data[2] = buffer >> 16;
	data[3] = buffer >> 8;
	data[4] = buffer;
	data[5] = 100;
	System::sendcheck(data, 6);

	return LV_RES_OK;
}
static lv_res_t fkt_Slide_max(lv_obj_t *btn)
{
	uint8_t data[6];
	int32_t buffer = 50000*4;
	data[0] = 0;
	data[0] |= 2<<4;
	data[0] |= 2;
	data[1] = buffer >> 24;
	data[2] = buffer >> 16;
	data[3] = buffer >> 8;
	data[4] = buffer;
	data[5] = 100;
	System::sendcheck(data, 6);

	return LV_RES_OK;
}



void createSettings(lv_obj_t * parent)
{
	uint8_t btn_height = 36;

	/*Button Back*/
    lv_obj_t *btn = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn, 150, btn_height);
    lv_obj_align(btn, parent, LV_ALIGN_IN_TOP_LEFT, 5, 0);
    lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, fkt_return);

    lv_obj_t *label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "Return");


	/*Button Jaw min*/
    lv_obj_t *btn_Jaw_min = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_Jaw_min, 115, btn_height);
    lv_obj_align(btn_Jaw_min, btn, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
    lv_btn_set_action(btn_Jaw_min, LV_BTN_ACTION_CLICK, fkt_Jaw_min);

    label = lv_label_create(btn_Jaw_min, NULL);
    lv_label_set_text(label, "Jaw min");

	/*Button Jaw max*/
    lv_obj_t *btn_Jaw_max = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_Jaw_max, 115, btn_height);
    lv_obj_align(btn_Jaw_max, btn_Jaw_min, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_Jaw_max, LV_BTN_ACTION_CLICK, fkt_Jaw_max);

    label = lv_label_create(btn_Jaw_max, NULL);
    lv_label_set_text(label, "Jaw max");


	/*Button Pitch min*/
    lv_obj_t *btn_Pitch_min = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_Pitch_min, 115, btn_height);
    lv_obj_align(btn_Pitch_min, btn_Jaw_min, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_btn_set_action(btn_Pitch_min, LV_BTN_ACTION_CLICK, fkt_Pitch_min);

    label = lv_label_create(btn_Pitch_min, NULL);
    lv_label_set_text(label, "Pitch min");

	/*Button Pitch max*/
    lv_obj_t *btn_Pitch_max = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_Pitch_max, 115, btn_height);
    lv_obj_align(btn_Pitch_max, btn_Pitch_min, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_Pitch_max, LV_BTN_ACTION_CLICK, fkt_Pitch_max);

    label = lv_label_create(btn_Pitch_max, NULL);
    lv_label_set_text(label, "Pitch max");


	/*Button Slide min*/
    lv_obj_t *btn_Slide_min = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_Slide_min, 115, btn_height);
    lv_obj_align(btn_Slide_min, btn_Pitch_min, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_btn_set_action(btn_Slide_min, LV_BTN_ACTION_CLICK, fkt_Slide_min);

    label = lv_label_create(btn_Slide_min, NULL);
    lv_label_set_text(label, "Slide left");

	/*Button Slide max*/
    lv_obj_t *btn_Slide_max = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_Slide_max, 115, btn_height);
    lv_obj_align(btn_Slide_max, btn_Slide_min, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_Slide_max, LV_BTN_ACTION_CLICK, fkt_Slide_max);

    label = lv_label_create(btn_Slide_max, NULL);
    lv_label_set_text(label, "Slide right");


	/*Button All min*/
    lv_obj_t *btn_All_min = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_All_min, 115, btn_height);
    lv_obj_align(btn_All_min, btn_Slide_min, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
    //TODO lv_btn_set_action(btn_All_min, LV_BTN_ACTION_CLICK, btn_returntomain);

    label = lv_label_create(btn_All_min, NULL);
    lv_label_set_text(label, "All left");

	/*Button All max*/
    lv_obj_t *btn_All_max = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_All_max, 115, btn_height);
    lv_obj_align(btn_All_max, btn_All_min, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    //TODO lv_btn_set_action(btn_All_max, LV_BTN_ACTION_CLICK, btn_returntomain);

    label = lv_label_create(btn_All_max, NULL);
    lv_label_set_text(label, "All right");
}
