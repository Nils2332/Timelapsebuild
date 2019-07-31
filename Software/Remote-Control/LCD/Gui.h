/*
 * Gui.h
 *
 *  Created on: 12.03.2019
 *      Author: Nils
 */

#ifndef GUI_H_
#define GUI_H_


#include "lvgl.h"




void createView();

void createHeader(lv_obj_t * parent);
void createMain(lv_obj_t * parent);
void createSettings(lv_obj_t * parent);


void label_refresher_task(void * p);
void label_calcpositions_task(void * p);
void readJoycon_task(void * p);
void battery_refresher(void * p);

lv_res_t fkt_return(lv_obj_t *btn);

void setscreen(uint8_t scrnr);

lv_res_t fkt_motorpw_action(lv_obj_t *btn);
lv_res_t fkt_startposition(lv_obj_t *btn);
lv_res_t fkt_runcommand(lv_obj_t *btn);

void setcommandbuttons();
void togglePrecision();

void setPage(uint8_t pgnumber);
int32_t getPosition(uint8_t axis);

#ifdef __cplusplus
extern "C" {
#endif





#ifdef __cplusplus
}
#endif

#endif /* GUI_H_ */
