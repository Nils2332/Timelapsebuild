/*
 * mvm.cpp
 *
 *  Created on: 01.04.2019
 *      Author: Nils
 */
#include "mvm.h"
#include "Gui.h"

#include "math.h"
#include "lvgl.h"
#include "joycon.h"
#include "App.h"

#include "System.h"


static lv_obj_t *btn_en_motor2;


static lv_obj_t *btn_jaw_mode;
static lv_obj_t *btn_pitch_mode;
static lv_obj_t *btn_slide_mode;

static uint8_t mvm_pospoint_action = 0;
static uint8_t mvm_pointno = 0;

static lv_style_t style_line1;
static lv_point_t line_points[] = {{(lv_coord_t)(23*mvm_pointno),0},{(lv_coord_t)(23*mvm_pointno),310}};
static lv_obj_t * line1;

static uint8_t mvm_mode[3][11] = {0};
static uint8_t mvm_points_enabled[3]= { 2, 2, 2};
static uint8_t mvm_points_enabledno[3][11]={{0,10},{0,10},{0,10}};
static uint8_t mvm_point_enabled[3][11] = {{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
static int32_t mvm_point[3][11] = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 12500, 12500, 12500, 12500, 12500, 12500, 12500, 12500, 12500, 12500, 12500}};

//static lv_task_t *task_mvm_settime;


static lv_obj_t *chart1;
static lv_obj_t *chart2;
static lv_obj_t *chart3;

static lv_obj_t *chart1_en;
static lv_obj_t *chart2_en;
static lv_obj_t *chart3_en;



static lv_obj_t *lbl_mvm_posjaw;
static lv_obj_t *lbl_mvm_pospitch;
static lv_obj_t *lbl_mvm_posslide;

static lv_chart_series_t * ser1;
static lv_chart_series_t * ser1_en;
static lv_chart_series_t * jaw_live;

static lv_chart_series_t * ser2;
static lv_chart_series_t * ser2_en;
static lv_chart_series_t * pitch_live;

static lv_chart_series_t * ser3;
static lv_chart_series_t * ser3_en;
static lv_chart_series_t * slide_live;


static lv_res_t mvm_set_jaw(lv_obj_t *btn);
static lv_res_t mvm_set_pitch(lv_obj_t *btn);
static lv_res_t mvm_set_slide(lv_obj_t *btn);


static lv_res_t fkt_mode(lv_obj_t *btn);


void calcSer(uint8_t no);
void label_modebtn(lv_obj_t *btn);


void mvm_position_update()
{
    char buffer[30];
    /*Jaw*/
    sprintf(buffer, "Jaw: %2.1f deg", (double)getPosition(0)*0.01125 );
    lv_label_set_text(lbl_mvm_posjaw, buffer);
    jaw_live->points[mvm_pointno] = getPosition(0);
    lv_chart_refresh(chart1_en);

    /*Pitch*/
    sprintf(buffer, "Pitch: %3.1f deg", getPosition(1)*0.01125 );
    lv_label_set_text(lbl_mvm_pospitch, buffer);
    pitch_live->points[mvm_pointno] = getPosition(1);
    lv_chart_refresh(chart2_en);

    /*Slide*/
    sprintf(buffer, "Slide: %3.0f mm", getPosition(2)*0.015 );
    lv_label_set_text(lbl_mvm_posslide, buffer);
    slide_live->points[mvm_pointno] = getPosition(2)/2;
    lv_chart_refresh(chart3_en);
}

void fkt_mvm_startposition()
{
	uint8_t data[7];

	for(uint8_t i = 0; i<3; i++){
		int32_t buffer = mvm_point[i][0]*4;
		if(i == 2) buffer *= 2;
		data[0] = 0;
		data[0] |= i<<4;	//Motor
		data[0] |= 2;		//Command
		data[1] = buffer >> 24;
		data[2] = buffer >> 16;
		data[3] = buffer >> 8;
		data[4] = buffer;
		data[5] = 100;
		data[6] = 1;
		System::sendcheck(data, 7);
	}
}

void fkt_btn_motor2(uint8_t command)
{
	lv_obj_t *label = lv_obj_get_child(btn_en_motor2, NULL);
	if(command == 0){
		lv_label_set_text(label, "Disconn.");
		lv_btn_set_state(btn_en_motor2, LV_BTN_STATE_INA);
	}
	if(command == 1){
		lv_label_set_text(label, "Motor OFF");
		lv_btn_set_state(btn_en_motor2, LV_BTN_STATE_REL);
	}
	if(command == 2){
		lv_label_set_text(label, "Motor ON");
		lv_btn_set_state(btn_en_motor2, LV_BTN_STATE_REL);
	}
}


void mvm_refresher_task(void * p)
{
	if(lv_obj_get_screen(btn_jaw_mode) == lv_scr_act())
	{
		/*Get and process Joycon Value*/
		JoyconUpdate();

		if(getJoycon(3) ==1 && mvm_pointno <10 && mvm_pospoint_action == 0){
			jaw_live->points[mvm_pointno] = -13000;
			pitch_live->points[mvm_pointno] = -13000;
			slide_live->points[mvm_pointno] = -13000;
			mvm_pointno++;
			mvm_pospoint_action =2;
		}
		if(getJoycon(3) <-0.75 && mvm_pointno >0 &&mvm_pospoint_action == 0){
			jaw_live->points[mvm_pointno] = -13000;
			pitch_live->points[mvm_pointno] = -13000;
			slide_live->points[mvm_pointno] = -13000;
			mvm_pointno--;
			mvm_pospoint_action =2;
		}

		if(mvm_pospoint_action > 0)mvm_pospoint_action--;

		/*Change vertical (time)line and move to (time)position*/
		if(mvm_pospoint_action == 1)
		{
			jaw_live->points[mvm_pointno] = getPosition(0);
			pitch_live->points[mvm_pointno] = getPosition(1);
			slide_live->points[mvm_pointno] = getPosition(2)/2;

			/* Vertical line*/
			uint16_t v_steps = LV_HOR_RES/10-1;

			line_points[0].x = v_steps*mvm_pointno;
			line_points[1].x = v_steps*mvm_pointno;

			lv_line_set_points(line1, line_points, 2);

			label_modebtn(btn_jaw_mode);
			label_modebtn(btn_pitch_mode);
			label_modebtn(btn_slide_mode);

			//Move to postition Sync TODO
			uint8_t data[7];
			int32_t buffer = ser1->points[mvm_pointno*10]*4;
			data[0] = 0;
			data[0] |= 0<<4;	//Motor
			data[0] |= 2;		//Command
			data[1] = buffer >> 24;
			data[2] = buffer >> 16;
			data[3] = buffer >> 8;
			data[4] = buffer;
			data[5] = 100;
			data[6] = 1;
			System::sendcheck(data, 7);


			buffer = ser2->points[mvm_pointno*10]*4;
			data[0] = 0;
			data[0] |= 1<<4;	//Motor
			data[0] |= 2;		//Command
			data[1] = buffer >> 24;
			data[2] = buffer >> 16;
			data[3] = buffer >> 8;
			data[4] = buffer;
			data[5] = 100;
			System::sendcheck(data, 7);


			buffer = ser3->points[mvm_pointno*10]*2*4;
			data[0] = 0;
			data[0] |= 2<<4;	//Motor
			data[0] |= 2;		//Command
			data[1] = buffer >> 24;
			data[2] = buffer >> 16;
			data[3] = buffer >> 8;
			data[4] = buffer;
			data[5] = 100;
			System::sendcheck(data, 7);
		}
	}
}

void createMoveGraph(lv_obj_t *parent)
{
	/*Return Button*/
    lv_obj_t *btn = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn, (LV_HOR_RES-10)/2, 32);
    lv_obj_align(btn, parent, LV_ALIGN_IN_TOP_LEFT, 5, 0);
    lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, fkt_return);

    lv_obj_t *label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "Return");


    btn_en_motor2 = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_en_motor2, (LV_HOR_RES-10)/2, 32);
    lv_obj_align(btn_en_motor2, btn, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_btn_set_action(btn_en_motor2, LV_BTN_ACTION_CLICK, fkt_motorpw_action);
    lv_btn_set_state(btn_en_motor2, LV_BTN_STATE_INA);

    label = lv_label_create(btn_en_motor2, NULL);
    lv_label_set_text(label, "Disconn.");



    /*Jaw Mode*/
    btn_jaw_mode = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn_jaw_mode, (LV_HOR_RES-10)/3, 32);
    lv_obj_align(btn_jaw_mode, btn, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_btn_set_action(btn_jaw_mode, LV_BTN_ACTION_CLICK, fkt_mode);

    label = lv_label_create(btn_jaw_mode, NULL);
    label_modebtn(btn_jaw_mode);


    /*Pitch Mode*/
    btn_pitch_mode = lv_btn_create(parent, btn_jaw_mode);
    lv_obj_align(btn_pitch_mode, btn_jaw_mode, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_pitch_mode, LV_BTN_ACTION_CLICK, fkt_mode);

    label = lv_label_create(btn_pitch_mode, NULL);
    label_modebtn(btn_pitch_mode);


    /*Slide Mode*/
    btn_slide_mode = lv_btn_create(parent, btn_jaw_mode);
    lv_obj_align(btn_slide_mode, btn_pitch_mode, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_btn_set_action(btn_slide_mode, LV_BTN_ACTION_CLICK, fkt_mode);

    label = lv_label_create(btn_slide_mode, NULL);
    label_modebtn(btn_slide_mode);


    /*chart 1*/
    chart1 = lv_chart_create(parent, NULL);
    lv_obj_set_size(chart1, LV_HOR_RES-10, 100);
    lv_obj_align(chart1, btn, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 32);
    lv_chart_set_type(chart1, LV_CHART_TYPE_LINE );
    lv_chart_set_series_opa(chart1, LV_OPA_100);
    lv_chart_set_series_width(chart1, 2);
    lv_chart_set_div_line_count(chart1, 3, 9);
    lv_chart_set_point_count(chart1, 101);
    lv_chart_set_range(chart1, -11112, 11112);

    chart1_en = lv_chart_create(chart1, chart1);
    lv_chart_set_div_line_count(chart1_en, 0, 0);
    lv_chart_set_type(chart1_en, LV_CHART_TYPE_POINT );
    lv_obj_align(chart1_en, chart1, LV_ALIGN_CENTER, 0, 0);
    lv_chart_set_series_opa(chart1_en, LV_OPA_100);
    lv_chart_set_series_width(chart1_en, 4);
    lv_chart_set_point_count(chart1_en, 11);
    lv_obj_set_opa_scale_enable(chart1_en, 1);
    lv_obj_set_opa_scale(chart1_en, LV_OPA_60);

    ser1_en = lv_chart_add_series(chart1_en, LV_COLOR_RED);
    jaw_live = lv_chart_add_series(chart1_en, LV_COLOR_PURPLE);

    for(uint8_t i=0; i<11; i++){
    	if(mvm_point_enabled[0][i]){
    		ser1_en->points[i] = mvm_point[0][i];
    	}
    	else{
    		ser1_en->points[i] = -13000;
    	}
    	jaw_live->points[i] = -13000;
    }
    jaw_live->points[mvm_pointno] = getPosition(0);
    lv_chart_refresh(chart1_en);

    lv_obj_t *btn2 = lv_btn_create(parent, NULL);
    lv_obj_set_size(btn2, LV_HOR_RES-10, 100);
    lv_obj_align(btn2, chart1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_opa_scale_enable(btn2, 1);
    lv_obj_set_opa_scale(btn2, LV_OPA_10);
    lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, mvm_set_jaw);

    lbl_mvm_posjaw = lv_label_create(parent, NULL);
    lv_obj_align(lbl_mvm_posjaw, chart1, LV_ALIGN_IN_TOP_LEFT, 2, 2);
    lv_obj_set_opa_scale_enable(lbl_mvm_posjaw, 1);
    lv_obj_set_opa_scale(lbl_mvm_posjaw, LV_OPA_60);


    /*chart 2*/
    chart2 = lv_chart_create(parent, chart1);
    lv_obj_align(chart2, chart1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 5);
    lv_chart_set_range(chart2, -8200, 8200);		//0.01125

    chart2_en = lv_chart_create(chart2, chart1_en);
    lv_chart_set_series_width(chart2_en, 4);
    lv_chart_set_range(chart2_en, -8200, 8200);
    ser2_en = lv_chart_add_series(chart2_en, LV_COLOR_RED);
    pitch_live = lv_chart_add_series(chart2_en, LV_COLOR_PURPLE);

    for(uint8_t i=0; i<11; i++){
    	if(mvm_point_enabled[1][i]){
    		ser2_en->points[i] = mvm_point[1][i];
    	}
    	else{
    		ser2_en->points[i] = -13000;
    	}
    	pitch_live->points[i] = -13000;
    }
    pitch_live->points[mvm_pointno] = getPosition(1);
    lv_chart_refresh(chart2_en);

    btn2 = lv_btn_create(parent, btn2);
    lv_obj_set_size(btn2, LV_HOR_RES-10, 100);
    lv_obj_align(btn2, chart2, LV_ALIGN_CENTER, 0, 0);
    lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, mvm_set_pitch);

    lbl_mvm_pospitch = lv_label_create(parent, lbl_mvm_posjaw);
    lv_obj_align(lbl_mvm_pospitch, chart2, LV_ALIGN_IN_TOP_LEFT, 2, 2);


    /*char 3*/
	chart3 = lv_chart_create(parent, chart1);

	lv_obj_align(chart3, chart2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 5);
	lv_chart_set_range(chart3, -100, 50000/2);

    chart3_en = lv_chart_create(chart3, chart1_en);
    lv_chart_set_series_width(chart3_en, 4);
    lv_chart_set_range(chart3_en, -100, 50000/2);
    ser3_en = lv_chart_add_series(chart3_en, LV_COLOR_RED);
    slide_live = lv_chart_add_series(chart3_en, LV_COLOR_PURPLE);

    for(uint8_t i=0; i<11; i++){
    	if(mvm_point_enabled[2][i]){
    		ser3_en->points[i] = mvm_point[2][i];
    	}
    	else{
    		ser3_en->points[i] = -13000;
    	}
    	slide_live->points[i] = -13000;
    }
    slide_live->points[mvm_pointno] = getPosition(2)/2;
    lv_chart_refresh(chart3_en);

    btn2 = lv_btn_create(parent, btn2);
	lv_obj_set_size(btn2, LV_HOR_RES - 10, 100);
	lv_obj_align(btn2, chart3, LV_ALIGN_CENTER, 0, 0);
	lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, mvm_set_slide);

    lbl_mvm_posslide = lv_label_create(parent, lbl_mvm_posjaw);
    lv_obj_align(lbl_mvm_posslide, chart3, LV_ALIGN_IN_TOP_LEFT, 2, 2);


	/*vertical selected time-indication line*/
	lv_style_copy(&style_line1, &lv_style_plain);
	style_line1.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
	style_line1.line.width = 3;

	line1 = lv_line_create(parent, NULL);
	lv_line_set_points(line1, line_points, 2);
	lv_obj_align(line1, chart1, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	lv_line_set_style(line1, &style_line1);



	ser1 = lv_chart_add_series(chart1, LV_COLOR_BLUE);
	calcSer(0);
	lv_chart_refresh(chart1);

	ser2 = lv_chart_add_series(chart2, LV_COLOR_GREEN);
	calcSer(1);
	lv_chart_refresh(chart2);

	ser3 = lv_chart_add_series(chart3, LV_COLOR_CYAN);
	calcSer(2);
	lv_chart_refresh(chart3);

}

static lv_res_t mvm_set_jaw(lv_obj_t *btn)
{
	uint8_t axis = 0;
	if(!mvm_point_enabled[axis][mvm_pointno] || mvm_pointno == 0 || mvm_pointno == 10){
		mvm_point_enabled[axis][mvm_pointno] = 1;
		mvm_point[axis][mvm_pointno] = getPosition(axis);//M1_position;
	}
	else{
		mvm_point_enabled[axis][mvm_pointno] = 0;
	}

	mvm_points_enabled[axis] = 0;
    for(uint8_t i=0; i<11; i++){
    	if(mvm_point_enabled[axis][i]){
    		ser1_en->points[i] = mvm_point[axis][i];
    		mvm_points_enabled[axis]++;
    		mvm_points_enabledno[axis][i] = i;
    	}
    	else{
    		ser1_en->points[i] = -13000;
    	}
    }
    lv_chart_refresh(chart1_en);

    label_modebtn(btn_jaw_mode);

    calcSer(axis);

	return LV_RES_OK;
}


static lv_res_t mvm_set_pitch(lv_obj_t *btn)
{
	uint8_t axis = 1;
	if(!mvm_point_enabled[axis][mvm_pointno] || mvm_pointno == 0 || mvm_pointno == 10){
		mvm_point_enabled[axis][mvm_pointno] = 1;
		mvm_point[axis][mvm_pointno] = getPosition(axis);//M2_position;
	}
	else{
		mvm_point_enabled[axis][mvm_pointno] = 0;
	}

	mvm_points_enabled[axis] = 0;
    for(uint8_t i=0; i<11; i++){
    	if(mvm_point_enabled[axis][i]){
    		ser2_en->points[i] = mvm_point[axis][i];
    		mvm_points_enabled[axis]++;
    		mvm_points_enabledno[axis][i] = i;
    	}
    	else{
    		ser2_en->points[i] = -13000;
    	}
    }
    lv_chart_refresh(chart2_en);

    label_modebtn(btn_pitch_mode);

    calcSer(axis);

	return LV_RES_OK;
}

static lv_res_t mvm_set_slide(lv_obj_t *btn)
{
	uint8_t axis = 2;
	if(!mvm_point_enabled[axis][mvm_pointno] || mvm_pointno == 0 || mvm_pointno == 10){
		mvm_point_enabled[axis][mvm_pointno] = 1;
		mvm_point[axis][mvm_pointno] = getPosition(axis)/2;//M3_position;
	}
	else{
		mvm_point_enabled[axis][mvm_pointno] = 0;
	}

	mvm_points_enabled[axis] = 0;
    for(uint8_t i=0; i<11; i++){
    	if(mvm_point_enabled[axis][i]){
    		ser3_en->points[i] = mvm_point[axis][i];
    		mvm_points_enabled[axis]++;
    		mvm_points_enabledno[axis][i] = i;
    	}
    	else{
    		ser3_en->points[i] = -13000;
    	}
    }
    lv_chart_refresh(chart3_en);

	label_modebtn(btn_slide_mode);

    calcSer(axis);

	return LV_RES_OK;
}


static lv_res_t fkt_mode(lv_obj_t *btn)
{
	uint8_t axis = 0;
	if(btn == btn_jaw_mode){
		axis = 0;
	}
	if(btn == btn_pitch_mode){
		axis = 1;
	}
	if(btn == btn_slide_mode){
		axis = 2;
	}
	if(mvm_mode[axis][mvm_pointno]){
		mvm_mode[axis][mvm_pointno] = 0;
	}
	else{
		mvm_mode[axis][mvm_pointno] = 1;
	}

	label_modebtn(btn);

	calcSer(axis);

    return LV_RES_OK;
}

void label_modebtn(lv_obj_t *btn){
	uint8_t axis = 0;
	char axistext[10];
	if(btn == btn_jaw_mode){
		axis = 0;
		sprintf(axistext, "Jaw");
	}
	if(btn == btn_pitch_mode){
		axis = 1;
		sprintf(axistext, "Pitch");
	}
	if(btn == btn_slide_mode){
		axis = 2;
		sprintf(axistext, "Slide");
	}
	lv_obj_t *label = lv_obj_get_child(btn, NULL);
    if(mvm_point_enabled[axis][mvm_pointno] && mvm_pointno){
    	lv_btn_set_state(btn, LV_BTN_STATE_REL);
        if(mvm_mode[axis][mvm_pointno]){
        	sprintf(axistext, "%s x^5", axistext);
        	lv_label_set_text(label, axistext);
        }
        else{
        	sprintf(axistext, "%s lin", axistext);
        	lv_label_set_text(label, axistext);
        }
    }
    else{
    	lv_btn_set_state(btn, LV_BTN_STATE_INA);
    	sprintf(axistext, "%s", axistext);
        lv_label_set_text(label, axistext);
    }
}


void calcSer(uint8_t no)
{
	uint8_t i;

	mvm_points_enabled[no] = 0;
	for(i=0; i<11; i++){
		if(mvm_point_enabled[no][i]){
			mvm_points_enabledno[no][mvm_points_enabled[no]]= i;
			mvm_points_enabled[no]++;
		}
	}

	for(i=0; i<mvm_points_enabled[no]; i++){

	}

	double c0, c1, c2, c3, c4, c5;
	c0 = 0, c1 = 0; c2 = 0; c3 = 0; c4 = 0, c5 = 0;

	int n = 0;
	int m = 0;

	double j1, j2, j3, j4, j5;
	double te, s0, se, a0, ae, v0, ve;

	double pos;

	double v[10];

	for(i = 0; i<11; i++){
		if(mvm_mode[no][mvm_points_enabledno[no][i]]==1){
			te=(mvm_points_enabledno[no][i]-mvm_points_enabledno[no][i-1])*10;
			s0 = mvm_point[no][mvm_points_enabledno[no][i-1]];
			se = mvm_point[no][mvm_points_enabledno[no][i]];

			v[i] = (se-s0)/te;
		}
		else{
			v[i] = 0;
		}
	}

	a0 = 0;
	ae = 0;

	for(i = 0; i<101; i++)
	{
		if(n == i)
		{
			te=(mvm_points_enabledno[no][m+1]-mvm_points_enabledno[no][m])*10;
			s0 = mvm_point[no][mvm_points_enabledno[no][m]];
			se = mvm_point[no][mvm_points_enabledno[no][m+1]];


			if(mvm_mode[no][mvm_points_enabledno[no][m+1]]==0){
				v0 = v[m];
				ve = v[m+2];

				c0 = s0;
				c1 = v0;
				c2 = 0;//a0/2;
				c3 = (ae-3*a0)/(2*te) - (4*ve+6*v0)/(pow(te,2)) + 10*(se-s0)/(pow(te,3));
				c4 = (3*a0-2*ae)/(pow(te,2)) + (8*v0+7*ve)/(pow(te,3)) + 15*(s0-se)/(pow(te,4));
				c5 = (ae-a0)/(2*pow(te,3)) - 3*(c1+ve)/(pow(te,4)) + 6*(se-c0)/(pow(te,5));
			}
			else{
				c0 = s0;
				c1 = (se-s0)/te;
				c2 = 0, c3 = 0, c4 = 0, c5 = 0;
			}

//			System::print("New spline: %d  %f %f %f %f %f %f\n", m, c0, c1, c2, c3, c4, c5);
//			System::print("s0: %f  se: %f  te: %f\n", s0, se, te);

			m++;
			n = mvm_points_enabledno[no][m]*10+1;
		}

		j1= i - mvm_points_enabledno[no][m-1]*10;
		j2= pow(j1, 2);
		j3= pow(j1, 3);
		j4= pow(j1, 4);
		j5= pow(j1, 5);

		pos = c0 + c1*j1 + c2*j2 + c3*j3 + c4*j4 + c5*j5;

		if(no == 0){
			ser1->points[i] = (int32_t)pos;
			//System::print("%d %f   %f\n", i , j1,  pos);
		}
		if(no == 1){
			ser2->points[i] = (int32_t)pos;
		}
		if(no == 2){
			ser3->points[i] = (int32_t)pos;
		}
	}
	if(no == 0){
		lv_chart_refresh(chart1);
	}
	if(no == 1){
		lv_chart_refresh(chart2);
	}
	if(no == 2){
		lv_chart_refresh(chart3);
	}
}

void sendpoints()
{
	uint8_t i,j;
	uint8_t data[9];

	for(i = 0; i<3; i++){
		uint8_t pointno = 0;
		for(j = 0; j <11; j++)
		{
			if(mvm_point_enabled[i][j]){

				int32_t buffer = mvm_point[i][j]*4;
				if(i == 2) buffer *= 2;
				data[0] = i<<4;	//Motor
				data[0] |= 7;		//Command
				data[1]	= pointno;
				data[2] = j;
				data[3] = mvm_mode[i][j];
				data[4] = buffer >> 24;
				data[5] = buffer >> 16;
				data[6] = buffer >> 8;
				data[7] = buffer;
				data[8] = mvm_points_enabled[i];
				System::sendcheck(data, 9);

				pointno++;
			}
		}
	}
}
